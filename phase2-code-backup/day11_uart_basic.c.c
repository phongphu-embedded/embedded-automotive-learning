#include <stdint.h>
#include "registers.h"
# define LOG_INTERVAL_MS 2000U

volatile uint32_t ms_tick = 0;


void TIM2_IRQHandler(void) {
	if (READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;
	}
}

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

int main(void) {
	uint32_t last_tick = 0;
	uint32_t current_mode = 1;
	uint32_t duty = 50;

	SET_BIT(RCC_APB2ENR, 2);  /* GPIOA */
	SET_BIT(RCC_APB2ENR, 14); /* USART1 */
	SET_BIT(RCC_APB1ENR, 0); /* Timer TIM2*/

	/* Set PA9 */
	CLEAR_BIT(GPIOA_CRH, 4); CLEAR_BIT(GPIOA_CRH, 5);
	CLEAR_BIT(GPIOA_CRH, 6); CLEAR_BIT(GPIOA_CRH, 7);
	SET_BIT(GPIOA_CRH, 4);
	SET_BIT(GPIOA_CRH, 5);
	SET_BIT(GPIOA_CRH, 7);

	/* Set PA10 */
	CLEAR_BIT(GPIOA_CRH, 8); CLEAR_BIT(GPIOA_CRH, 9);
	CLEAR_BIT(GPIOA_CRH, 10); CLEAR_BIT(GPIOA_CRH, 11);
	SET_BIT(GPIOA_CRH, 10);

	/* Cau hinh USART1: 9600 baud, 8N1 */
	/* BRR = 8MHz / 9600 = 833 */
	USART1_BRR = 833;

	/* SET Timer 1ms */
	TIM2_PSC = 7;
	TIM2_ARR = 999;

	/* Bat TX (bit 3) va USART (bit 13) */
	SET_BIT(USART1_CR1, 3); /* TE = Transmitter Enable */
	SET_BIT(USART1_CR1, 13); /* UE = USART Enable */

	SET_BIT(TIM2_DIER, 0);
	SET_BIT(NVIC_ISER0, 28);

	SET_BIT(TIM2_CR1, 0);

	for (;;) {

		if (ms_tick - last_tick >= LOG_INTERVAL_MS) {
			last_tick = ms_tick;

		uart_send_string("[LOG] Thoi gian: ");
		uart_send_number(ms_tick);
		uart_send_string("ms | Mode: ");
		uart_send_number(current_mode);
		uart_send_string(" | Duty: ");
		uart_send_number(duty);
		uart_send_string("\r\n");
		}
	}
}
