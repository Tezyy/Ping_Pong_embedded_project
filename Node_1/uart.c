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


void USART_Init( unsigned int ubrr ) // Initialize function of register USART
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */ 
UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ0); // If more speed desired we can use 1stop bit : UCSRC = (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01);
}


void USART_Transmit( unsigned char data ) //USART transmit data function 
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR = data;
}


unsigned char USART_Receive( void ) //USART receiving data function
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}

/*Use of global interrupt to notify when a new character is received*/
void USART_Notif_receive_data (void)
{ 
/*use of UCSRB0 but UCSRB1 exists ?? --> UCSRB is a register for USART control, and there's typically
only one UCSRB for each USART peripheral(unless there are multiple USART peripherals, like USART0 and USART1).
On an ATmega microcontroller with two USARTs, we have UCSR0B for USART0 and UCSR1B for USART1.
We can configure the second UART with the equivalent UCSR1B register.*/
    UCSR0B |= (1<<RXCIE0); //To enable interrupt-based reception we need to set HIGH the Receive Complete Interrupt Enable(RXCIE) bit in UCSRB
    sei();
}

/*When the RXC flag is set (when a byte is received), this ISR is executed.*/
ISR(USART0_RXC_vect)//Vector name on https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-F889605B-692F-493A-8BE7-F0FBACF1715B
{ 
    unsigned char received_data = UDR0; //take the char which is in UDR register
    /* Possibility to make a "circular buffer" to store multiple data */
}

/*Link printf function */
void link_printf(void)
{
    fdevopen(USART_Transmit,USART_Receive);
}
