#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

//#include "bit_macros.h"
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
