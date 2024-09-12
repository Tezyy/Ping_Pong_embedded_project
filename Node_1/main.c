#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

//#include "bit_macros.h"
#include "uart.h"
#include "sram.h"



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

/*PART 2 : LATCH AND RAM */
#define BASE_ADDRESS 0x1000
#define LED_PORT 0x0800
void xmem_init ( void )
{
      MCUCR |= (1 << SRE ); // enable XMEM
      SFIOR |= (1 << XMM0); // Mask PC7-PC4 for JTAG
}


void xmem_write(uint8_t data, uint16_t addr)
{
      volatile char *ext_mem = (char *)BASE_ADDRESS;
      ext_mem[addr] = data;
}


void latch_test()
{
      NULL;
}

int main(void)
{
      USART_Init(MYUBRR);
      //xmem_init();
      init_printf();
    while(1)
    {
        //unsigned char mess = USART_Receive();
            //USART_Transmit(mess);
            //printf("ouioui");
            //_delay_ms(1000);
            
            _delay_ms(1000);
            printf("1");
            PORTA=0x00000000;
            _delay_ms(1000);
            PORTE=0x10;
            _delay_ms(1000);
            PORTA=0x11111111;
            _delay_ms(1000);
            PORTE=0x00;
            _delay_ms(1000);
            PORTE=0x10;
    }
}
