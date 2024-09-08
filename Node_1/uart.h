#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

// Constants and Macros
#define F_CPU 4915200UL // CPU Clock Speed
#define BAUD 9600       // Baud rate for UART communication
#define MYUBRR F_CPU/16/BAUD-1 // Calculating UBRR value based on baud rate and clock speed

// Function prototypes
void USART_Init(unsigned int ubrr);               // Function to initialize USART
void USART_Transmit(unsigned char data);          // Function to transmit a single character over USART
unsigned char USART_Receive(void);                // Function to receive a single character from USART
void USART_Notif_receive_data(void);              // Function to enable notification when data is received
ISR(USART0_RXC_vect);                             // Interrupt Service Routine for received data
void link_printf(void);                           // Function to link printf to USART

#endif // USART_DRIVER_H

