#include <stdint.h>
#include "registers.h"

volatile uint32_t ms_tick = 0;
uint32_t last_tick_DIM = 0;
uint32_t last_tick_MODE = 0;
uint32_t last_tick_TOGGLE = 0;
uint32_t duty = 800;

uint32_t current_mode = 0;
uint32_t current_button = 0;
uint32_t last_button = 0;

void TIM2_IRQHandler(void) {
	if (READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;

	}
}

void ap_dung_mode(int mode) {
    if (mode == 0) {
        TIM1_CCR1 = 0;
        CLEAR_BIT(GPIOA_ODR, 0);
        CLEAR_BIT(GPIOA_ODR, 1);
    }
    if (mode == 1) {
        TIM1_CCR1 = duty;
        SET_BIT(GPIOA_ODR, 0);
        CLEAR_BIT(GPIOA_ODR, 1);
    }
    if (mode == 2) {
        TIM1_CCR1 = 0;
        CLEAR_BIT(GPIOA_ODR, 0);
        if (ms_tick - last_tick_TOGGLE >= 500) {
            last_tick_TOGGLE = ms_tick;
            TOGGLE_BIT(GPIOA_ODR, 1);
        }
    }
}
int main(void) {



	SET_BIT(RCC_APB2ENR, 2);
	SET_BIT(RCC_APB2ENR, 11);
	SET_BIT(RCC_APB1ENR, 0);

	/* LED hau PA0*/
	CLEAR_BIT(GPIOA_CRL, 0); CLEAR_BIT(GPIOA_CRL, 1);
	CLEAR_BIT(GPIOA_CRL, 2); CLEAR_BIT(GPIOA_CRL, 3);
	SET_BIT(GPIOA_CRL, 1);

	/* LED bao nguy */
	CLEAR_BIT(GPIOA_CRL, 4); CLEAR_BIT(GPIOA_CRL, 5);
	CLEAR_BIT(GPIOA_CRL, 6); CLEAR_BIT(GPIOA_CRL, 7);
	SET_BIT(GPIOA_CRL, 5);

	/* Set up MODE PA4*/
	CLEAR_BIT(GPIOA_CRL, 16); CLEAR_BIT(GPIOA_CRL, 17);
	CLEAR_BIT(GPIOA_CRL, 18); CLEAR_BIT(GPIOA_CRL, 19);
	SET_BIT(GPIOA_CRL, 19);
	SET_BIT(GPIOA_ODR, 4);

	/* SET up PA5*/
	CLEAR_BIT(GPIOA_CRL, 20); CLEAR_BIT(GPIOA_CRL, 21);
	CLEAR_BIT(GPIOA_CRL, 22); CLEAR_BIT(GPIOA_CRL, 23);
	SET_BIT(GPIOA_CRL, 23);
	SET_BIT(GPIOA_ODR, 5);

	CLEAR_BIT(GPIOA_CRH, 0); CLEAR_BIT(GPIOA_CRH, 1);
	CLEAR_BIT(GPIOA_CRH, 2); CLEAR_BIT(GPIOA_CRH, 3);
	/* Set 1011cho PA8 */
	SET_BIT(GPIOA_CRH, 0);
	SET_BIT(GPIOA_CRH, 1);
	SET_BIT(GPIOA_CRH, 3);

	/* SET UP tần số Hz */
	TIM1_PSC = 7;
	TIM1_ARR = 999;

	TIM1_CCMR1 = (6 << 4);
	SET_BIT(TIM1_CCER, 0);
	SET_BIT(TIM1_BDTR, 15);
	TIM1_CCR1 = 0; /* reset duty ve 0 khi khoi dong */

	TIM2_PSC = 7;
	TIM2_ARR = 999;

	SET_BIT(TIM2_DIER, 0);

	SET_BIT(NVIC_ISER0, 28);

	SET_BIT(TIM1_CR1, 0);
	TIM1_CCR1 = 0;
	SET_BIT(TIM2_CR1, 0);

	for (;;) {



		if (ms_tick - last_tick_MODE >= 50) {
			last_tick_MODE = ms_tick;
			if(READ_BIT(GPIOA_IDR, 4)) {
				   current_button = 0;
			} else {
				current_button = 1;
			}

			if(current_button == 1 && last_button == 0) {
				if (current_mode == 0) {
					current_mode = 1;
				    duty = 800;
				} else if (current_mode == 1) {
					current_mode = 2;
					TIM1_CCR1 = 0;
				} else if (current_mode == 2) {
					current_mode = 0;
				}
			}
			last_button = current_button;
		}


		if (current_mode == 1) {
		        if (ms_tick - last_tick_DIM >= 50) {
		            last_tick_DIM = ms_tick;
		            if (READ_BIT(GPIOA_IDR, 5) == 0) {
		                duty -= 100;
		            }
		            if (duty <= 100) { duty = 100; }
		            if (duty >= 800) { duty = 800; }
		        }
		    }



		ap_dung_mode(current_mode);
	}

}
