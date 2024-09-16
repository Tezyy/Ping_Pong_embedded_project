#ifndef UART_H
#define UART_H

// Define CPU clock frequency
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <avr/io.h>  // For MCUCR, SFIOR, etc.
#include <stdio.h>   // For printf
#include <stdlib.h>  // For rand, srand
#include <stdint.h>  // For standard integer types like uint8_t, uint16_t

// Define USART parameters
#define FOSC 4915200UL // Clock frequency
#define BAUD 9600      // Baud rate
#define MYUBRR FOSC/16/BAUD-1

// Function Prototypes
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
int uart_putchar(char c, FILE *stream);
void init_printf(void);

#endif /* UART_H */
