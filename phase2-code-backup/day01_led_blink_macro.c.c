#include <stdint.h>

#define SET_BIT(reg, bit)  ((reg) |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~ (1UL << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^= (1UL << (bit)))
#define READ_BIT(reg, bit)  ((reg) & (1UL << (bit)))

#define RCC_BASE  0x40021000UL
#define GPIOA_BASE 0x40010800UL


#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE + 0x18)))
#define GPIOA_CRL (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))
#define GPIOA_IDR (*((volatile uint32_t *)(GPIOA_BASE + 0x08)))

int main(void) {
	/*Bat clock GPIOA*/
	SET_BIT(RCC_APB2ENR, 2);
	/* RCC_APB2ENR |= (1 << 2); */

	/*PA0 = output LED*/
	CLEAR_BIT(GPIOA_CRL, 0);
	CLEAR_BIT(GPIOA_CRL, 1);
	CLEAR_BIT(GPIOA_CRL, 2);
	CLEAR_BIT(GPIOA_CRL, 3);
	/* GPIOA_CRL &= ~ (0xF <<0); */
	SET_BIT(GPIOA_CRL, 1);
	/* GPIOA_CRL |= (0x2 << 0)*/

	/*PA1 = input pull up (NUT BAM)*/
	CLEAR_BIT(GPIOA_CRL, 4);
	CLEAR_BIT(GPIOA_CRL, 5);
	CLEAR_BIT(GPIOA_CRL, 6);
	CLEAR_BIT(GPIOA_CRL, 7);
	/*GPIOA_CRL &= ~(0xF <<4);*/
	SET_BIT(GPIOA_CRL, 7);
	/*GPIOA_CRL |= (0x8 <<4);*/
	SET_BIT(GPIOA_ODR, 1);
	/*GPIOA_ODR |= (1 <<1);*/

	for(;;) {
		if (READ_BIT(GPIOA_IDR, 1)) /* GPIOA_IDR & (1 << 1)) */
				{
			CLEAR_BIT(GPIOA_ODR, 0);
			/*GPIOA_ODR &= ~(1 << 0);*/
		} else {
			SET_BIT(GPIOA_ODR, 0);
			/* GPIOA_ODR |= (1 <<0);*/
		}
	}
}
