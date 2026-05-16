#include <stdint.h>

#define RCC_BASE     0x40021000UL
#define GPIOA_BASE   0x40010800UL
#define RCC_APB2ENR  (*((volatile uint32_t *)(RCC_BASE   + 0x18)))
#define GPIOA_CRL    (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR    (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))

int main(void) {
    /* Bat clock GPIOA */
    RCC_APB2ENR |= (1 << 2);

    /* Cau hinh PA0 la output 2MHz push-pull */
    GPIOA_CRL &= ~(0xF << 0);
    GPIOA_CRL |=  (0x2 << 0);

    for (;;) {
        int i = 0;
        GPIOA_ODR |=  (1 << 0);  /* bat LED */
        for (i = 0; i < 100000; i++) {}

        GPIOA_ODR &= ~(1 << 0);  /* tat LED */
        for (i = 0; i < 100000; i++) {}
    }
}
