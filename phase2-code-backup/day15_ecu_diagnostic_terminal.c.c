#include <stdint.h>
#include "registers.h"

/* Circular buffer — size luy thua 2, dung bitmask */
#define RX_BUF_SIZE 16U
#define LED_PIN0    0U
#define LED_PIN1    1U
#define LED_PIN2    2U
#define TIME_SENSOR 1000U

#define TEMP_MAX 99U
#define TEMP_MIN 70U
#define TEMP_THRESHOLD 90U

#define VOLT_MAX 129U
#define VOLT_MIN 110U
#define VOLT_THRESHOLD 125U

#define RPM_MAX 3799U
#define RPM_MIN 800U
#define RPM_THRESHOLD 3500U

volatile char     rx_buf[RX_BUF_SIZE];
volatile uint32_t rx_head = 0U; /* ISR ghi vao day */
volatile uint32_t rx_tail = 0U; /* main loop doc tu day */


volatile uint32_t ms_tick = 0U;
void TIM2_IRQHandler(void) {
	if (READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;
	}
}

uint32_t last_tick_sensor = 0U;


uint32_t nhiet_do = 70U;
uint32_t dien_ap = 120U;
uint32_t rpm = 800U;


/* ===================== */
/* Ham UART              */
/* ===================== */
void uart_send_char(char c) {
    while (!READ_BIT(USART1_SR, 7)) {}
    USART1_DR = (uint32_t)c;
}

void uart_send_string(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        uart_send_char(str[i]);
        i++;
    }
}

void uart_send_number(uint32_t n) {
	if (n / 10 != 0) {
		uart_send_number(n / 10);
	}

	uart_send_char((n % 10) + '0');
}

/* ISR — goi tu dong khi co byte moi */
void USART1_IRQHandler(void) {
    if (READ_BIT(USART1_SR, 5)) { /* RXNE = 1 */
        char c = (char)USART1_DR; /* doc tu dong xoa co RXNE */
        /* Ghi vao buffer neu chua day */
        uint32_t next = (rx_head + 1U) & (RX_BUF_SIZE - 1U);
        if (next != rx_tail) {    /* kiem tra buffer day */
            rx_buf[rx_head] = c;
            rx_head = next;
        }
    }
}

/* Doc 1 byte tu buffer — tra ve 0 neu rong */
char buf_read(void) {
    char c = 0;
    if (rx_tail != rx_head) {
        c = rx_buf[rx_tail];
        rx_tail = (rx_tail + 1U) & (RX_BUF_SIZE - 1U);
    }
    return c;
}

/* Kiem tra buffer co du lieu khong */
int buf_available(void) {
    return (rx_tail != rx_head) ? 1 : 0;
}

/* ===================== */
/* Xu ly lenh            */
/* ===================== */

void xu_ly_lenh(char lenh) {
    switch (lenh) {

    case 'R':
    	uart_send_string("[DATA] Nhiet do: ");
        uart_send_number(nhiet_do);
        uart_send_string("C | ");
    	uart_send_string("Dien ap: ");
        uart_send_number(dien_ap);
        uart_send_string("V | ");
    	uart_send_string("RPM: ");
        uart_send_number(rpm);
        uart_send_string("\r\n");
    break;

    case 'T':
    	uart_send_string("[TIME] Uptime: ");
        uart_send_number(ms_tick);
        uart_send_string("ms\r\n");
    break;

    case 'W':
    	uart_send_string(READ_BIT(GPIOA_ODR, LED_PIN0) ?
    	     "[WARN] Trang thai: CANH BAO" : "[WARN] Trang thai: BINH THUONG");
    	uart_send_string("\r\n");
    break;

    case 'H':
    	uart_send_string("R= READ | T= TIME | W= WARNING | H= HELP\r\n");
    break;

    default:
        uart_send_string("[ERROR] Lenh khong xac dinh\r\n");
        return; /* Khong echo lenh sai */
    }

    uart_send_string("OK: ");
    uart_send_char(lenh);
    uart_send_string("\r\n");
}

void update_data(void) {
	if (ms_tick - last_tick_sensor >= TIME_SENSOR) {
		last_tick_sensor = ms_tick;
		/* update TEMP */
		if (nhiet_do >= TEMP_MAX) {
			nhiet_do = TEMP_MIN;
		} else {
			nhiet_do = 70 + (ms_tick / 1000) % 30;
	      }
		/* update VOLT */
		if (dien_ap >= VOLT_MAX) {
			dien_ap = VOLT_MIN;
		} else {
			dien_ap = 110 + (ms_tick / 1000) % 20;
	      }
		/* update RPM */
		if (rpm >= RPM_MAX) {
			rpm = RPM_MIN;
		} else {
			rpm = 800 + (ms_tick / 1000) % 3000;
	      }
    }
}

void checking_threshold(void) {
	if (nhiet_do > TEMP_THRESHOLD || dien_ap > VOLT_THRESHOLD || rpm > RPM_THRESHOLD) {
		SET_BIT(GPIOA_ODR, LED_PIN0);
	} else {
		CLEAR_BIT(GPIOA_ODR, LED_PIN0);
	}
}

/* ===================== */
/* Main                  */
/* ===================== */
int main(void) {
    SET_BIT(RCC_APB2ENR, 2);  /* GPIOA  */
    SET_BIT(RCC_APB2ENR, 14); /* USART1 */
    SET_BIT(RCC_APB1ENR, 0); /* TIM2 */

    /* PA0 = output 2MHz */
    CLEAR_BIT(GPIOA_CRL, 0);  CLEAR_BIT(GPIOA_CRL, 1);
    CLEAR_BIT(GPIOA_CRL, 2);  CLEAR_BIT(GPIOA_CRL, 3);
    SET_BIT(GPIOA_CRL, 1);

    /* PA9 = TX AF PP 50MHz */
    CLEAR_BIT(GPIOA_CRH, 4); CLEAR_BIT(GPIOA_CRH, 5);
    CLEAR_BIT(GPIOA_CRH, 6); CLEAR_BIT(GPIOA_CRH, 7);
    SET_BIT(GPIOA_CRH, 4);
    SET_BIT(GPIOA_CRH, 5);
    SET_BIT(GPIOA_CRH, 7);

    /* PA10 = RX Input Floating */
    CLEAR_BIT(GPIOA_CRH, 8);  CLEAR_BIT(GPIOA_CRH, 9);
    CLEAR_BIT(GPIOA_CRH, 10); CLEAR_BIT(GPIOA_CRH, 11);
    SET_BIT(GPIOA_CRH, 10);

    USART1_BRR = 833U;
    SET_BIT(USART1_CR1, 2);  /* RE */
    SET_BIT(USART1_CR1, 3);  /* TE */
    SET_BIT(USART1_CR1, 5);  /* RXNEIE — bat UART RX interrupt */
    SET_BIT(USART1_CR1, 13); /* UE */

    /* Bat USART1 interrupt trong NVIC — IRQ37, ISER1 bit 5 */
    SET_BIT(NVIC_ISER1, 5);

	SET_BIT(TIM2_DIER, 0); /* interrupt */
	SET_BIT(NVIC_ISER0, 28); /* interrupt trong NVIC */

	/* TIM2 interrupt 1 ms */
	TIM2_PSC = 7;
	TIM2_ARR = 999;

	/* TIM2 interrupt ON */
	SET_BIT(TIM2_CR1, 0);

    uart_send_string("=== Mini Diagnostic Terminal  ===\r\n");
    uart_send_string("R= READ | T= TIME | W= WARNING | H= HELP\r\n");

    for (;;) {
        /* Main loop xu ly lenh khi buffer co du lieu */
        if (buf_available()) {
            char lenh = buf_read();
            xu_ly_lenh(lenh);
        }

    update_data();
    checking_threshold();
    }
}
