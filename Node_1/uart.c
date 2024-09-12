//Utile ou pas de define dans le .c, suffisant dans le main ?
//#define F_CPU 4915200UL 
//#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "uart.h"

#define FOSC 4915200UL
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init( unsigned int ubrr )
{
      /* Set baud rate */
      UBRR0H = (unsigned char)(ubrr>>8);
      UBRR0L = (unsigned char)ubrr;
      /* Enable receiver and transmitter */
      UCSR0B = (1<<RXEN0)|(1<<TXEN0);
      /* Set frame format: 8data, 2stop bit */
      UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}


void USART_Transmit( unsigned char data )
{
      /* Wait for empty transmit buffer */
      while ( !( UCSR0A & (1<<UDRE0)) )
      ;
      /* Put data into buffer, sends the data */
      UDR0 = data;
}


unsigned char USART_Receive( void )
{
      /* Wait for data to be received */
      while ( !(UCSR0A & (1<<RXC0)) )
      ;
      /* Get and return received data from buffer */
      return UDR0;
}


int uart_putchar(char c, FILE *stream)
{
      if (c == '\n') {
            USART_Transmit('\r');  // Send carriage return before newline
      }
      USART_Transmit(c);  // Transmit the character
      return 0;
}


void init_printf(void)
{
      static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
      stdout = &uart_stdout;  // Set stdout to use uart_putchar
}
