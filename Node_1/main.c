#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

//#include "bit_macros.h"
#include "uart.h"
#include "sram.h"


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
