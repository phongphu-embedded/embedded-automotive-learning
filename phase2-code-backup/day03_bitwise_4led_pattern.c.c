#include <stdint.h>

#define SET_BIT(reg, bit)   ((reg)  |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg)  &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit)   ((reg)  ^= (1UL << (bit)))
#define READ_BIT(reg, bit)   ((reg)  & (1UL << (bit)))


#define RCC_BASE     0x40021000UL
#define GPIOA_BASE   0x40010800UL
#define RCC_APB2ENR  (*((volatile uint32_t *)(RCC_BASE   + 0x18)))
#define GPIOA_CRL    (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR    (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))

int main(void) {
	int pattern = 1;
	int i = 0;
	int j = 0;
    /* Bat clock GPIOA */
    SET_BIT(RCC_APB2ENR, 2);
	/*RCC_APB2ENR |= (1 << 2);*/
    CLEAR_BIT(GPIOA_CRL, 0);  CLEAR_BIT(GPIOA_CRL, 1);
    CLEAR_BIT(GPIOA_CRL, 2);  CLEAR_BIT(GPIOA_CRL, 3);
    SET_BIT(GPIOA_CRL, 1);   /* PA0 output 2MHz */

    CLEAR_BIT(GPIOA_CRL, 4);  CLEAR_BIT(GPIOA_CRL, 5);
    CLEAR_BIT(GPIOA_CRL, 6);  CLEAR_BIT(GPIOA_CRL, 7);
    SET_BIT(GPIOA_CRL, 5);   /* PA1 output 2MHz */

    CLEAR_BIT(GPIOA_CRL, 8);  CLEAR_BIT(GPIOA_CRL, 9);
    CLEAR_BIT(GPIOA_CRL, 10); CLEAR_BIT(GPIOA_CRL, 11);
    SET_BIT(GPIOA_CRL, 9);   /* PA2 output 2MHz */

    CLEAR_BIT(GPIOA_CRL, 12); CLEAR_BIT(GPIOA_CRL, 13);
    CLEAR_BIT(GPIOA_CRL, 14); CLEAR_BIT(GPIOA_CRL, 15);
    SET_BIT(GPIOA_CRL, 13);  /* PA3 output 2MHz */


    for (;;) {

    if (pattern == 1) {
        SET_BIT(GPIOA_ODR, 0);
        for (i = 0; i < 100000; i++) {}
        CLEAR_BIT(GPIOA_ODR, 0);
        for (i = 0; i < 100000; i++) {}

        SET_BIT(GPIOA_ODR, 1);
        for (i = 0; i < 100000; i++) {}
        CLEAR_BIT(GPIOA_ODR, 1);
        for (i = 0; i < 100000; i++) {}

        SET_BIT(GPIOA_ODR, 2);
        for (i = 0; i < 100000; i++) {}
        CLEAR_BIT(GPIOA_ODR, 2);
        for (i = 0; i < 100000; i++) {}

        SET_BIT(GPIOA_ODR, 3);
        for (i = 0; i < 100000; i++) {}
        CLEAR_BIT(GPIOA_ODR, 3);
        for (i = 0; i < 100000; i++) {}
        pattern = 2;
    }

    if (pattern ==2) {
    	SET_BIT(GPIOA_ODR, 0);
    	CLEAR_BIT(GPIOA_ODR, 1);
    	SET_BIT(GPIOA_ODR, 2);
    	CLEAR_BIT(GPIOA_ODR, 3);
    	for (j = 0; j < 100000; j++) {}

    	TOGGLE_BIT(GPIOA_ODR, 0);
    	TOGGLE_BIT(GPIOA_ODR, 1);
    	TOGGLE_BIT(GPIOA_ODR, 2);
    	TOGGLE_BIT(GPIOA_ODR, 3);
    	for (j = 0; j < 100000; j++) {}
    	pattern = 1;
    }
    }
}
