#include <stdint.h>
#include "registers.h"

#define LED_PIN0 0U /* PA0 */
#define LED_PIN1 1U /* PA1 */
#define LED_PIN2 2U /* PA2 */

void uart_send_char(char c) {
    while (!READ_BIT(USART1_SR, 7)) {}
    USART1_DR = (uint32_t)c;
}

void uart_send_string(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        uart_send_char(str[i]);
        i++;
    }
}

char uart_receive_char(void) {
    /* Cho RXNE = 1 — co byte moi trong DR */
    while (!READ_BIT(USART1_SR, 5)) {}
    return (char)USART1_DR;
}

void in_trang_thai(void) {
	  if (READ_BIT(GPIOA_ODR, LED_PIN0)) {
		  uart_send_string("LED1: BAT | ");
	  } else {
		  uart_send_string("LED1: TAT | ");
	  }

	  if (READ_BIT(GPIOA_ODR, LED_PIN1)) {
		  uart_send_string("LED2: BAT | ");
	  } else {
		  uart_send_string("LED2: TAT | ");
	  }

	  if (READ_BIT(GPIOA_ODR, LED_PIN2)) {
		  uart_send_string("LED3: BAT\r\n");
	  } else {
		  uart_send_string("LED3: TAT\r\n");
	  }
}

void xu_ly_lenh(char lenh) {
    switch (lenh) {
        case '1':
        TOGGLE_BIT(GPIOA_ODR, LED_PIN0);
        break;

        case '2':
        TOGGLE_BIT(GPIOA_ODR, LED_PIN1);
        break;

        case '3':
        TOGGLE_BIT(GPIOA_ODR, LED_PIN2);
        break;

        case 'A':
        SET_BIT(GPIOA_ODR, LED_PIN0);
        SET_BIT(GPIOA_ODR, LED_PIN1);
        SET_BIT(GPIOA_ODR, LED_PIN2);
        break;

        case 'Z':
        CLEAR_BIT(GPIOA_ODR, LED_PIN0);
        CLEAR_BIT(GPIOA_ODR, LED_PIN1);
        CLEAR_BIT(GPIOA_ODR, LED_PIN2);
        break;

        case 'S':
        in_trang_thai();
		break;
    }
        uart_send_string("Nhan lenh: ");
        uart_send_char(lenh);
        uart_send_string("\r\n");
}

int main(void) {
    /* Bat clock */
    SET_BIT(RCC_APB2ENR, 2);  /* GPIOA  */
    SET_BIT(RCC_APB2ENR, 14); /* USART1 */

    /* PA0 = output 2MHz (LED) */
    CLEAR_BIT(GPIOA_CRL, 0); CLEAR_BIT(GPIOA_CRL, 1);
    CLEAR_BIT(GPIOA_CRL, 2); CLEAR_BIT(GPIOA_CRL, 3);
    SET_BIT(GPIOA_CRL, 1);

    /* PA1 = output 2MHz (LED) */
    CLEAR_BIT(GPIOA_CRL, 4); CLEAR_BIT(GPIOA_CRL, 5);
    CLEAR_BIT(GPIOA_CRL, 6); CLEAR_BIT(GPIOA_CRL, 7);
    SET_BIT(GPIOA_CRL, 5);

    /* PA2 = output 2MHz (LED) */
    CLEAR_BIT(GPIOA_CRL, 8); CLEAR_BIT(GPIOA_CRL, 9);
    CLEAR_BIT(GPIOA_CRL, 10); CLEAR_BIT(GPIOA_CRL, 11);
    SET_BIT(GPIOA_CRL, 9);

    /* PA9 = TX AF PP 50MHz */
    CLEAR_BIT(GPIOA_CRH, 4); CLEAR_BIT(GPIOA_CRH, 5);
    CLEAR_BIT(GPIOA_CRH, 6); CLEAR_BIT(GPIOA_CRH, 7);
    SET_BIT(GPIOA_CRH, 4);
    SET_BIT(GPIOA_CRH, 5);
    SET_BIT(GPIOA_CRH, 7);

    /* PA10 = RX Input Floating */
    CLEAR_BIT(GPIOA_CRH, 8);  CLEAR_BIT(GPIOA_CRH, 9);
    CLEAR_BIT(GPIOA_CRH, 10); CLEAR_BIT(GPIOA_CRH, 11);
    SET_BIT(GPIOA_CRH, 10);

    /* USART1: 9600 baud */
    USART1_BRR = 833U;

    /* Bat TX + RX + USART */
    SET_BIT(USART1_CR1, 2);  /* RE = Receiver Enable  */
    SET_BIT(USART1_CR1, 3);  /* TE = Transmitter Enable */
    SET_BIT(USART1_CR1, 13); /* UE = USART Enable      */

    uart_send_string("=== ECU UART CONTROL ===\r\n");
    uart_send_string("A = ON LED | Z = OFF LED | S = Printf state\r\n");
    uart_send_string("1 = TOG LED1 | 2 = TOG LED2 | 3 = TOG LED3\r\n");
    uart_send_string("========================\r\n");

    for (;;) {
        char lenh = uart_receive_char();
        xu_ly_lenh(lenh);
    }
}
