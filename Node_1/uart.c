/* <INFORMATION>    
This code contains sample code parts from ATmega162 Datasheet*/

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 4.9152E8 //Clock Speed
#include <util/delay.h>
#include  <stdint.h>

#define BAUD 9600 //Baud USART
#define MYUBRR F_CPU/16/BAUD-1 

void USART_Init( unsigned int ubrr ) // Initialize of register USART
{
/* Set baud rate */
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 2stop bit */ // If more speed desired we can use 1stop bit : UCSRC = (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01);
UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

/*Transmitting data*/

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) )
;
/* Put data into buffer, sends the data */
UDR = data;
}

/*receiving data*/

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) )
;
/* Get and return received data from buffer */
return UDR;
}

/*Use of global interrupt to notify when a new character is received*/

void USART_notif_receive_data (void){ //use of UCSRB0 but UCSRB1 exists ??
    UCSRB |= (1<<RXCIE)
}

ISR(USART0_RXC_vect){ //Vector name on https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-F889605B-692F-493A-8BE7-F0FBACF1715B
    unsigned char received_data = UDR; //take the char which is in UDR register

    /* Possibility to make a "circular buffer" to store multiple data */
}

/*Link printf function */

void link_printf(void){
    fdevopen(USART_Transmit,USART_Receive);
}
