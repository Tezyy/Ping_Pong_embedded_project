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

        // Transmit a character (echo back)
        unsigned char received = USART_Receive(); // Receive data
        USART_Transmit(received);  // Send it back to the terminal (echo)
	
	// Testing the printf
 	printf("\nhello world!\n");

}

void exercise2(void) {

	//SRAM

	char data = 'c';

	volatile char* ext_ram = 0x1000;

	SRAM_test();

	while(1) {
		ext_ram[0x000] = data;
		//printf("OLED command\n");
		_delay_ms(3000);
		ext_ram[0x300] = data;
		//printf("OLED data\n");
		_delay_ms(3000);
		ext_ram[0x400] = data;
		//printf("ADC\n");
		_delay_ms(3000);
		ext_ram[0x800] = data;
		//printf("SRAM\n");
		_delay_ms(3000);
	}

}
*/


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
          
    return 0;
}
