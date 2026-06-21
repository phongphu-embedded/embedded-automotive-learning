#include <stdint.h>
#include "registers.h"

/* Circular buffer — size luy thua 2, dung bitmask */
#define RX_BUF_SIZE 16U
#define LED_PIN0    0U
#define LED_PIN1    1U
#define LED_PIN2    2U

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
uint32_t last_tick = 0U;
uint32_t blink_time = 500U;
uint32_t blinking = 0U;



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
void in_trang_thai(void) {
    uart_send_string(READ_BIT(GPIOA_ODR, LED_PIN0) ?
                     "LED1: BAT | " : "LED1: TAT | ");
    uart_send_string(READ_BIT(GPIOA_ODR, LED_PIN1) ?
                     "LED2: BAT | " : "LED2: TAT | ");
    uart_send_string(READ_BIT(GPIOA_ODR, LED_PIN2) ?
                     "LED3: BAT\r\n" : "LED3: TAT\r\n");
}

void xu_ly_lenh(char lenh) {
    switch (lenh) {
        case 'B':
        	blink_time = 500U;
            blinking = 1U;
        	break;

        case 'T':
        	 blinking = 0U;
        	CLEAR_BIT(GPIOA_ODR, LED_PIN0);break;

        case 'F':
        	if (blink_time >= 250) blink_time -= 250;
        	blinking = 2U;
        	 break;

        case 'S':
        	uart_send_string("[STATUS] Tick: ");
            uart_send_number(ms_tick);
            uart_send_string(" ms | ");
            uart_send_string(READ_BIT(GPIOA_ODR, LED_PIN0) ?
            		"Blink: ON | Speed: " : "Blink: OFF | Speed: ");
            uart_send_number(blink_time);
            uart_send_string("ms\r\n");
            break;

        default:
            uart_send_string("Lenh khong hop le\r\n");
            return; /* Khong echo lenh sai */
    }
    uart_send_string("OK: ");
    uart_send_char(lenh);
    uart_send_string("\r\n");
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

	TIM2_PSC = 7;
	TIM2_ARR = 999;

	SET_BIT(TIM2_CR1, 0); /* bat bo dem */

    uart_send_string("=== ECU UART INTERRUPT MODE ===\r\n");
    uart_send_string("B=LED 500ms | T=LED OFF | F=GAIN SPEED | S=Status\r\n");

    for (;;) {
        /* Main loop xu ly lenh khi buffer co du lieu */
        if (buf_available()) {
            char lenh = buf_read();
            xu_ly_lenh(lenh);
        }

    	if (ms_tick - last_tick >= blink_time && blinking > 0U) {
    		last_tick = ms_tick;
    		TOGGLE_BIT(GPIOA_ODR, LED_PIN0);
    	}

    }
}
