#include <stdint.h>

#define SET_BIT(reg, bit)  ((reg) |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^= (1UL << (bit)))
#define READ_BIT(reg, bit)  ((reg) & (1UL << (bit)))

#define RCC_BASE 0x40021000UL
#define GPIOA_BASE 0x40010800UL

#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE +  0x18)))
#define GPIOA_CRL (*((volatile uint32_t *)(GPIOA_BASE +  0x00)))
#define GPIOA_ODR (*((volatile uint32_t *)(GPIOA_BASE +  0x0C)))
#define GPIOA_IDR (*((volatile uint32_t *)(GPIOA_BASE +  0x08)))
int main(void) {
	int i = 0;
	int current_state = 0;
	int last_btn_state = 0;
	int pattern = 0;
	/* open clock*/
	SET_BIT(RCC_APB2ENR, 2);

	/*set output 2MHz PA0*/
	CLEAR_BIT(GPIOA_CRL, 0); CLEAR_BIT(GPIOA_CRL, 1);
	CLEAR_BIT(GPIOA_CRL, 2); CLEAR_BIT(GPIOA_CRL, 3);
	SET_BIT(GPIOA_CRL, 1);

	/*set output 2MHz PA1*/
	CLEAR_BIT(GPIOA_CRL, 4); CLEAR_BIT(GPIOA_CRL, 5);
    CLEAR_BIT(GPIOA_CRL, 6); CLEAR_BIT(GPIOA_CRL, 7);
	SET_BIT(GPIOA_CRL, 5);

	/*set output 2MHz PA2*/
	CLEAR_BIT(GPIOA_CRL, 8); CLEAR_BIT(GPIOA_CRL, 9);
	CLEAR_BIT(GPIOA_CRL, 10); CLEAR_BIT(GPIOA_CRL, 11);
    SET_BIT(GPIOA_CRL, 9);

    /*set output 2MHz PA3*/
    CLEAR_BIT(GPIOA_CRL, 12); CLEAR_BIT(GPIOA_CRL, 13);
    CLEAR_BIT(GPIOA_CRL, 14); CLEAR_BIT(GPIOA_CRL, 15);
    SET_BIT(GPIOA_CRL, 13);

    /*set input btn1 PA4*/
    CLEAR_BIT(GPIOA_CRL, 16); CLEAR_BIT(GPIOA_CRL, 17);
    CLEAR_BIT(GPIOA_CRL, 18); CLEAR_BIT(GPIOA_CRL, 19);
    SET_BIT(GPIOA_CRL, 19);

    /*set input btn2 PA5*/
    CLEAR_BIT(GPIOA_CRL, 20); CLEAR_BIT(GPIOA_CRL, 21);
    CLEAR_BIT(GPIOA_CRL, 22); CLEAR_BIT(GPIOA_CRL, 23);
    SET_BIT(GPIOA_CRL, 23);

    SET_BIT(GPIOA_ODR, 4);
    SET_BIT(GPIOA_ODR, 5);

    for (;;) {

    	if (READ_BIT(GPIOA_IDR, 4)) {
    		current_state = 0;
    	} else {
    		current_state = 1;
    	}

    	if (current_state == 1 && last_btn_state == 0) {
    		pattern = !pattern;
    	}
    	last_btn_state = current_state;

    	if (READ_BIT(GPIOA_IDR, 5) == 0) {
    		CLEAR_BIT(GPIOA_ODR, 0);
    		CLEAR_BIT(GPIOA_ODR, 1);
    		CLEAR_BIT(GPIOA_ODR, 2);
    		CLEAR_BIT(GPIOA_ODR, 3);
    	} else {
    		if (pattern == 0) {
    			/*pattern 0*/
    			    	/* blink LED 1 */
    			    	SET_BIT(GPIOA_ODR, 0);
    			    	for (i = 0; i < 125; i++);
    			    	CLEAR_BIT(GPIOA_ODR, 0);
    			    	for (i = 0; i < 125; i++);

    			    	/* blink LED 2 */
    			    	SET_BIT(GPIOA_ODR, 1);
    			    	for (i = 0; i < 125; i++);
    			    	CLEAR_BIT(GPIOA_ODR, 1);
    			    	for (i = 0; i < 125; i++);

    			    	/* blink LED 3 */
    			    	SET_BIT(GPIOA_ODR, 2);
    			    	for (i = 0; i < 125; i++);
    			    	CLEAR_BIT(GPIOA_ODR, 2);
    			    	for (i = 0; i < 125; i++);

    			    	/* blink LED 4 */
    			    	SET_BIT(GPIOA_ODR, 3);
    			    	for (i = 0; i < 125; i++);
    			    	CLEAR_BIT(GPIOA_ODR, 3);
    			    	for (i = 0; i < 125 ; i++);
    		} else {
    			/*pattern 1*/
    			    	SET_BIT(GPIOA_ODR, 0);
    			    	CLEAR_BIT(GPIOA_ODR, 1);
    			    	SET_BIT(GPIOA_ODR, 2);
    			    	CLEAR_BIT(GPIOA_ODR, 3);
    			    	for (i = 0; i < 500; i++);

    			    	TOGGLE_BIT(GPIOA_ODR, 0);
    			    	TOGGLE_BIT(GPIOA_ODR, 1);
    			    	TOGGLE_BIT(GPIOA_ODR, 2);
    			    	TOGGLE_BIT(GPIOA_ODR, 3);
    			    	for (i = 0; i < 500; i++);
    		}
    	}


    }
    }
