#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

#include "bit_macros.h"
#include "uart.h"
#include "sram.h"

/*
void exercise1(void) {

	unsigned char mess = USART_Receive();
	USART_Transmit(mess);
	printf("ouioui");
	_delay_ms(1000);

}

void exercise2(void) {
	DDRE = 0b10; //Sets ALE (pin 1 on port E) as output.
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	PORTA = 0b000001; //Sending an adress.

	_delay_ms(2000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.

	_delay_ms(2000);

	PORTA = 0b01010101; //Sends out new address.

	_delay_ms(2000);

	PORTE = 0b10; //Old address is removed  and the new one is sent through.
}


}
*/


int main(void)
{
USART_Init(MYUBRR);
	//XMEM_init();
	init_printf();
          
    while(1)
    {	
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
          
    return 0;
}
