#include <stdint.h>
#include "registers.h"


volatile uint32_t ms_tick = 0;
void TIM2_IRQHandler(void) {
	if (READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;
	}
}

int main(void) {

	uint32_t last_tick_500 = 0;
	uint32_t last_tick_1000 = 0;
	uint32_t last_tick_3000 = 0;

	SET_BIT(RCC_APB2ENR, 2);
	SET_BIT(RCC_APB1ENR, 0);

	CLEAR_BIT(GPIOA_CRL, 0);CLEAR_BIT(GPIOA_CRL, 1);
	CLEAR_BIT(GPIOA_CRL, 2);CLEAR_BIT(GPIOA_CRL, 3);
	SET_BIT(GPIOA_CRL, 1);

	CLEAR_BIT(GPIOA_CRL, 4);CLEAR_BIT(GPIOA_CRL, 5);
	CLEAR_BIT(GPIOA_CRL, 6);CLEAR_BIT(GPIOA_CRL, 7);
	SET_BIT(GPIOA_CRL, 5);

	CLEAR_BIT(GPIOA_CRL, 8);CLEAR_BIT(GPIOA_CRL, 9);
	CLEAR_BIT(GPIOA_CRL, 10);CLEAR_BIT(GPIOA_CRL, 11);
	SET_BIT(GPIOA_CRL, 9);

	SET_BIT(TIM2_DIER, 0); /* interrupt */
	SET_BIT(NVIC_ISER0, 28); /* interrupt trong NVIC */


	TIM2_PSC = 7;
	TIM2_ARR = 999;

	SET_BIT(TIM2_CR1, 0); /* bat bo dem */



	for(;;) {

		if (ms_tick - last_tick_500 >= 500) {
			last_tick_500 = ms_tick;
			TOGGLE_BIT(GPIOA_ODR, 0);
		}
		if (ms_tick - last_tick_1000 >= 1000) {
			last_tick_1000 = ms_tick;
			TOGGLE_BIT(GPIOA_ODR, 1);
		}
		if (ms_tick - last_tick_3000 >= 3000) {
			last_tick_3000 = ms_tick;
			TOGGLE_BIT(GPIOA_ODR, 2);
		}

	}
	return 0;
}
