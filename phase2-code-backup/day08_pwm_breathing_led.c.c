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
	uint32_t last_tick = 0;
	int duty = 0;
	int huong = 1; /* 1 = tang, -1 = giam */

	/* mo clock */
	SET_BIT(RCC_APB2ENR, 2);
	SET_BIT(RCC_APB2ENR, 11); /* TIM 1*/
	SET_BIT(RCC_APB1ENR, 0);

	/* set mode 1011*/
	CLEAR_BIT(GPIOA_CRH, 0); CLEAR_BIT(GPIOA_CRH, 1);
	CLEAR_BIT(GPIOA_CRH, 2); CLEAR_BIT(GPIOA_CRH, 3);
	SET_BIT(GPIOA_CRH, 0);
	SET_BIT(GPIOA_CRH, 1);
	SET_BIT(GPIOA_CRH, 3);

	/* TIM1 1kHZ */
	TIM1_PSC = 7;
	TIM1_ARR = 999;

	/*PWWM*/
	TIM1_CCMR1 = (6 << 4); /*bit 4-6 = 110 = OCM1*/

	/*output CH1*/
	SET_BIT(TIM1_CCER, 0); /*CCE1*/

	 /* Bat Main Output Enable (TIM1 can them buoc nay) */
	SET_BIT(TIM1_BDTR, 15); /*MOE = 1*/

	 /* Duty cycle ban dau = 50% */
	TIM1_CCR1 = 500;

	/* Bat TIM1 */
	SET_BIT(TIM1_CR1, 0);

	/* Cau hinh TIM2 ngat 10ms */
	TIM2_PSC = 7;
	TIM2_ARR = 9999; /*10ms*/
	SET_BIT(TIM2_DIER, 0);
	SET_BIT(NVIC_ISER0, 28);
	SET_BIT(TIM2_CR1, 0);

	for (;;) {
		if (ms_tick - last_tick >= 2) {
			last_tick = ms_tick;
			duty += huong * 10;

			if (duty >= 1000) {duty = 1000; huong = -1;	}
		    if (duty <= 0) {duty = 0; huong = 1;}

		    TIM1_CCR1 = (uint32_t)duty;

	}



	}
}
