#include <stdint.h>
#include "registers.h"

volatile uint32_t ms_tick = 0;

void TIM2_IRQHandler(void) {
	if(READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;
	}
}

int main(void) {
	uint32_t last_tick = 0;
	int last_state_btn1 = 0;
	int last_state_btn2 = 0;
	int duty = 0;
	int doc_6;
	int doc_7;

	SET_BIT(RCC_APB2ENR, 2); /*GPIOA*/
	SET_BIT(RCC_APB2ENR, 11); /*TIM1*/
	SET_BIT(RCC_APB1ENR, 0); /*TIM2*/

	CLEAR_BIT(GPIOA_CRH, 0); CLEAR_BIT(GPIOA_CRH, 1);
	CLEAR_BIT(GPIOA_CRH, 2); CLEAR_BIT(GPIOA_CRH, 3);
	SET_BIT(GPIOA_CRH, 0);
	SET_BIT(GPIOA_CRH, 1);
	SET_BIT(GPIOA_CRH, 3);

	CLEAR_BIT(GPIOA_CRL, 24); CLEAR_BIT(GPIOA_CRL, 25);
	CLEAR_BIT(GPIOA_CRL, 26); CLEAR_BIT(GPIOA_CRL, 27);
	SET_BIT(GPIOA_CRL, 27);
	SET_BIT(GPIOA_ODR, 6);

	CLEAR_BIT(GPIOA_CRL, 28); CLEAR_BIT(GPIOA_CRL, 29);
	CLEAR_BIT(GPIOA_CRL, 30); CLEAR_BIT(GPIOA_CRL, 31);
	SET_BIT(GPIOA_CRL, 31);
	SET_BIT(GPIOA_ODR, 7);

	TIM1_PSC = 7;
	TIM1_ARR = 999;

	TIM1_CCMR1 = ( 6 << 4);
	TIM1_CCR1 = 0;

	SET_BIT(TIM1_CCER, 0); /*cho phep tin hieu tu CCMR1 di qua GPIOA*/

	SET_BIT(TIM1_BDTR, 15);

	SET_BIT(TIM1_CR1, 0);

	TIM2_PSC = 7;
	TIM2_ARR = 999;

	SET_BIT(TIM2_DIER, 0);
	SET_BIT(NVIC_ISER0, 28);

	SET_BIT(TIM2_CR1, 0);

	for (;;) {
		if (ms_tick - last_tick >= 50) {
			last_tick = ms_tick;

			if (READ_BIT(GPIOA_IDR, 6) == 0) {
				doc_6 = 1;
			} else {
				doc_6 = 0;
			}

			if (doc_6 == 1 && last_state_btn1 == 0) {
				duty += 100;
			}
			last_state_btn1 = doc_6;

			if (READ_BIT(GPIOA_IDR, 7) == 0) {
				doc_7 = 1;
			} else {
				doc_7 = 0;
			}

			if (doc_7 == 1 && last_state_btn2 == 0) {
				duty -= 100;
			}
			last_state_btn2 = doc_7;

			if(duty >= 1000) {duty = 1000;}
			if(duty <= 0) {duty = 0;}

			TIM1_CCR1 = duty;
		}

	}

}
