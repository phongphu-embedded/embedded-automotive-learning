#include <stdint.h>

#define SET_BIT(reg, bit)    ((reg) |=  (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^=  (1UL << (bit)))
#define READ_BIT(reg, bit)   ((reg) &   (1UL << (bit)))

#define RCC_BASE     0x40021000UL
#define GPIOA_BASE   0x40010800UL
#define TIM2_BASE    0x40000000UL

#define RCC_APB2ENR  (*((volatile uint32_t *)(RCC_BASE   + 0x18)))
#define RCC_APB1ENR  (*((volatile uint32_t *)(RCC_BASE   + 0x1C)))
#define GPIOA_CRL    (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR    (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))
#define TIM2_CR1     (*((volatile uint32_t *)(TIM2_BASE  + 0x00)))
#define TIM2_SR      (*((volatile uint32_t *)(TIM2_BASE  + 0x10)))
#define TIM2_PSC     (*((volatile uint32_t *)(TIM2_BASE  + 0x28)))
#define TIM2_ARR     (*((volatile uint32_t *)(TIM2_BASE  + 0x2C)))

int main(void) {
	/* Bat clock GPIOA va TIM2 */
	SET_BIT(RCC_APB2ENR, 2);
	SET_BIT(RCC_APB1ENR, 0);

	/*PAO output 2MHz */
	CLEAR_BIT(GPIOA_CRL, 0); CLEAR_BIT(GPIOA_CRL, 1);
	CLEAR_BIT(GPIOA_CRL, 2); CLEAR_BIT(GPIOA_CRL, 3);
	SET_BIT(GPIOA_CRL, 1);

	/* cau hinh TIM2: ngat moi 500ms */
	/* T = (PSC+1)(ARR+1)/8MHz = (7999+1)(499+1)/8000000 = 0.5s */
	TIM2_PSC = 7999;
	TIM2_ARR = 999;

	/* bat tim 2*/
	SET_BIT(TIM2_CR1, 0); /* bit 0 = CEN (Counter Enable) */

	 for (;;) {
		 /* Cho co UIF bat len (bit 0 cua SR) */
		 if (READ_BIT(TIM2_SR, 0)) {
			 CLEAR_BIT(TIM2_SR, 0);    /* xoa co UIF */
			 TOGGLE_BIT(GPIOA_ODR, 0); /* toggle LED  */
		 }

	 }

}
