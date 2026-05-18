#include <stdint.h>

#define SET_BIT(reg, bit)    ((reg) |=  (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^=  (1UL << (bit)))
#define READ_BIT(reg, bit)   ((reg) &   (1UL << (bit)))

#define RCC_BASE    0x40021000UL
#define GPIOA_BASE  0x40010800UL

#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE   + 0x18)))
#define GPIOA_CRL   (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR   (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))
#define GPIOA_IDR   (*((volatile uint32_t *)(GPIOA_BASE + 0x08)))

/* ===================== */
/* Ham tien ich          */
/* ===================== */

void tat_tat_ca_den(void) {
    CLEAR_BIT(GPIOA_ODR, 0);
    CLEAR_BIT(GPIOA_ODR, 1);
    CLEAR_BIT(GPIOA_ODR, 2);
    CLEAR_BIT(GPIOA_ODR, 3);
    CLEAR_BIT(GPIOA_ODR, 4);
    CLEAR_BIT(GPIOA_ODR, 5);
}

void delay_ms(int ms) {
    int i = 0;
    int j = 0;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 500; j++) {}
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
    int i    = 0;
    int buoc = 0;

    /* Bat clock GPIOA */
    SET_BIT(RCC_APB2ENR, 2);

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

    for (;;) {

        /* Kiem tra nut khan cap truoc */
    	if (doc_nut_khan_cap() == 1) {
    	    while (doc_nut_khan_cap() == 1) {
    	        tat_tat_ca_den();
    	        SET_BIT(GPIOA_ODR, 1);
    	        SET_BIT(GPIOA_ODR, 4);

    	        /* Chia nho delay, kiem tra nut lien tuc */
    	        for (i = 0; i < 30; i++) {
    	            delay_ms(10);
    	            if (doc_nut_khan_cap() == 0) { break; }
    	        }

    	        tat_tat_ca_den();

    	        for (i = 0; i < 30; i++) {
    	            delay_ms(10);
    	            if (doc_nut_khan_cap() == 0) { break; }
    	        }
    	    }
    	    /* Tat het den truoc khi quay ve chu ki */
    	    tat_tat_ca_den();
    	    buoc = 0;
    	}

            else if (buoc == 0) {
            /* Buoc 0: A xanh, B do — 3 giay */
            tat_tat_ca_den();
            SET_BIT(GPIOA_ODR, 2); /* xanh A */
            SET_BIT(GPIOA_ODR, 3); /* do B   */
            for (i = 0; i < 300; i++) {
                delay_ms(10);
                if (doc_nut_khan_cap() == 1) { break; }
            }
            buoc++;

        } else if (buoc == 1) {
            /* Buoc 1: A vang, B do — 1 giay */
            tat_tat_ca_den();
            SET_BIT(GPIOA_ODR, 1); /* vang A */
            SET_BIT(GPIOA_ODR, 3); /* do B   */
            for (i = 0; i < 100; i++) {
                delay_ms(10);
                if (doc_nut_khan_cap() == 1) { break; }
            }
            buoc++;

        } else if (buoc == 2) {
            /* Buoc 2: A do, B xanh — 3 giay */
            tat_tat_ca_den();
            SET_BIT(GPIOA_ODR, 0); /* do A   */
            SET_BIT(GPIOA_ODR, 5); /* xanh B */
            for (i = 0; i < 300; i++) {
                delay_ms(10);
                if (doc_nut_khan_cap() == 1) { break; }
            }
            buoc++;

        } else {
            /* Buoc 3: A do, B vang — 1 giay */
            tat_tat_ca_den();
            SET_BIT(GPIOA_ODR, 0); /* do A   */
            SET_BIT(GPIOA_ODR, 4); /* vang B */
            for (i = 0; i < 100; i++) {
                delay_ms(10);
                if (doc_nut_khan_cap() == 1) { break; }
            }
            buoc = 0;
        }
    }
}
