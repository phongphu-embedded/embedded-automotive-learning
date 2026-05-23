#include <stdint.h>
#include "registers.h"

volatile uint32_t ms_tick = 0;

void tat_tat_ca_den(void) {
    CLEAR_BIT(GPIOA_ODR, 0);
    CLEAR_BIT(GPIOA_ODR, 1);
    CLEAR_BIT(GPIOA_ODR, 2);
    CLEAR_BIT(GPIOA_ODR, 3);
    CLEAR_BIT(GPIOA_ODR, 4);
    CLEAR_BIT(GPIOA_ODR, 5);
}

void TIM2_IRQHandler(void) {
	if(READ_BIT(TIM2_SR, 0)) {
		CLEAR_BIT(TIM2_SR, 0);
		ms_tick++;
	}
}

int doc_nut_khan_cap(void) {
    if (READ_BIT(GPIOA_IDR, 6) == 0) {
        return 1; /* dang nhan */
    } else {
        return 0; /* chua nhan */
    }
}

/* ===================== */
/* Ham chinh             */
/* ===================== */

int main(void) {
    int buoc = 0;
    uint32_t last_tick_buoc = 0;
    uint32_t last_tick_nhay_vang = 0;

    /* Bat clock GPIOA */
    SET_BIT(RCC_APB2ENR, 2);
    SET_BIT(RCC_APB1ENR, 0);

    /* PA0 = output 2MHz (den do huong A) */
    CLEAR_BIT(GPIOA_CRL, 0); CLEAR_BIT(GPIOA_CRL, 1);
    CLEAR_BIT(GPIOA_CRL, 2); CLEAR_BIT(GPIOA_CRL, 3);
    SET_BIT(GPIOA_CRL, 1);

    /* PA1 = output 2MHz (den vang huong A) */
    CLEAR_BIT(GPIOA_CRL, 4); CLEAR_BIT(GPIOA_CRL, 5);
    CLEAR_BIT(GPIOA_CRL, 6); CLEAR_BIT(GPIOA_CRL, 7);
    SET_BIT(GPIOA_CRL, 5);

    /* PA2 = output 2MHz (den xanh huong A) */
    CLEAR_BIT(GPIOA_CRL, 8);  CLEAR_BIT(GPIOA_CRL, 9);
    CLEAR_BIT(GPIOA_CRL, 10); CLEAR_BIT(GPIOA_CRL, 11);
    SET_BIT(GPIOA_CRL, 9);

    /* PA3 = output 2MHz (den do huong B) */
    CLEAR_BIT(GPIOA_CRL, 12); CLEAR_BIT(GPIOA_CRL, 13);
    CLEAR_BIT(GPIOA_CRL, 14); CLEAR_BIT(GPIOA_CRL, 15);
    SET_BIT(GPIOA_CRL, 13);

    /* PA4 = output 2MHz (den vang huong B) */
    CLEAR_BIT(GPIOA_CRL, 16); CLEAR_BIT(GPIOA_CRL, 17);
    CLEAR_BIT(GPIOA_CRL, 18); CLEAR_BIT(GPIOA_CRL, 19);
    SET_BIT(GPIOA_CRL, 17);

    /* PA5 = output 2MHz (den xanh huong B) */
    CLEAR_BIT(GPIOA_CRL, 20); CLEAR_BIT(GPIOA_CRL, 21);
    CLEAR_BIT(GPIOA_CRL, 22); CLEAR_BIT(GPIOA_CRL, 23);
    SET_BIT(GPIOA_CRL, 21);

    /* PA6 = input pull-up (nut khan cap) */
    CLEAR_BIT(GPIOA_CRL, 24); CLEAR_BIT(GPIOA_CRL, 25);
    CLEAR_BIT(GPIOA_CRL, 26); CLEAR_BIT(GPIOA_CRL, 27);
    SET_BIT(GPIOA_CRL, 27);
    SET_BIT(GPIOA_ODR, 6); /* chon pull-up */

    SET_BIT(TIM2_DIER, 0);
    SET_BIT(NVIC_ISER0, 28);

    TIM2_PSC = 7;
    TIM2_ARR = 999;

    SET_BIT(TIM2_CR1, 0);

    for (;;) {

        /* Kiem tra nut khan cap truoc */
    	if (doc_nut_khan_cap() == 1) {
    		buoc = 0;
    		tat_tat_ca_den();
    	    if (ms_tick - last_tick_nhay_vang >= 300) {
    	        last_tick_nhay_vang = ms_tick;

    	        TOGGLE_BIT(GPIOA_ODR, 1);
    	        TOGGLE_BIT(GPIOA_ODR, 4);
    	        }
    	} else if (buoc == 0 && last_tick_buoc == 0) {
    		   last_tick_buoc = ms_tick;
            /* Buoc 0: A xanh, B do — 3 giay */

            if (ms_tick - last_tick_buoc >= 3000) {
               last_tick_buoc = ms_tick;
               tat_tat_ca_den();
               SET_BIT(GPIOA_ODR, 2); /* xanh A */
               SET_BIT(GPIOA_ODR, 3); /* do B   */
               buoc++;
            }
        } else if (buoc == 1) {
            /* Buoc 1: A vang, B do — 1 giay */
            if (ms_tick - last_tick_buoc >= 1000) {
                last_tick_buoc = ms_tick;
                tat_tat_ca_den();
                SET_BIT(GPIOA_ODR, 1); /* vang A */
                SET_BIT(GPIOA_ODR, 3); /* do B   */
                buoc++;
            }
        } else if (buoc == 2) {
            /* Buoc 2: A do, B xanh — 3 giay */
            if (ms_tick - last_tick_buoc >= 3000) {
                last_tick_buoc = ms_tick;
                tat_tat_ca_den();
                SET_BIT(GPIOA_ODR, 0); /* do A   */
                SET_BIT(GPIOA_ODR, 5); /* xanh B */
                buoc++;
            }
        } else {
            /* Buoc 3: A do, B vang — 1 giay */
            if (ms_tick - last_tick_buoc >= 1000) {
                last_tick_buoc = ms_tick;
                tat_tat_ca_den();
                SET_BIT(GPIOA_ODR, 0); /* do A   */
                SET_BIT(GPIOA_ODR, 4); /* vang B */
                buoc = 0;
            }
        }
    }
    return 0;
}

