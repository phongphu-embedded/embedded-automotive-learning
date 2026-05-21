/* registers.h */
#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/* Macro bitwise */
#define SET_BIT(reg, bit)    ((reg) |=  (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^=  (1UL << (bit)))
#define READ_BIT(reg, bit)   ((reg) &   (1UL << (bit)))

/* Base addresses */
#define RCC_BASE    0x40021000UL
#define GPIOA_BASE  0x40010800UL
#define TIM2_BASE   0x40000000UL

/* RCC */
#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE + 0x18)))
#define RCC_APB1ENR (*((volatile uint32_t *)(RCC_BASE + 0x1C)))

/* GPIOA */
#define GPIOA_CRL   (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR   (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))
#define GPIOA_IDR   (*((volatile uint32_t *)(GPIOA_BASE + 0x08)))

/* TIM2 */
#define TIM2_CR1    (*((volatile uint32_t *)(TIM2_BASE + 0x00)))
#define TIM2_DIER   (*((volatile uint32_t *)(TIM2_BASE + 0x0C)))
#define TIM2_SR     (*((volatile uint32_t *)(TIM2_BASE + 0x10)))
#define TIM2_PSC    (*((volatile uint32_t *)(TIM2_BASE + 0x28)))
#define TIM2_ARR    (*((volatile uint32_t *)(TIM2_BASE + 0x2C)))

/* NVIC */
#define NVIC_ISER0  (*((volatile uint32_t *)0xE000E100UL))

#endif /* REGISTERS_H */
