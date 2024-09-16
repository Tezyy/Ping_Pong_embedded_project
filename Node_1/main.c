#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"
#include "sram.h"

void exercise1 (void){
		unsigned char mess = USART_Receive();
		_delay_ms(1000);
        USART_Transmit(mess);
        printf("ouioui");
        _delay_ms(1000);
}

void exercise2 (void){
	DDRE = 0b10; //Sets ALE (pin 1 on port E) as output.
	DDRA = 0xFF; //Because we read from PORTA we need to set it as an output.
	
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	PORTA = 0b00000011; //Sending an adress.
	_delay_ms(2000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(2000);
	
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	PORTA = 0b00000000; //Sending an adress.
	_delay_ms(2000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(2000);
}
void exercise2_bis (void){
	//SRAM start:         0x1800    1100 000000000
	//SRAM end:           0x1FFF    1111 111111111
	//ADC start:          0x1400    1010 000000000
	//ADC end:            0x17FF    1011 111111111
	//OLED-data start:    0x1200    1001 000000000
	//OLED-data end:      0x13FF    1001 111111111
	//OLED-command start: 0x1000    1000 000000000
	//OLED-command end:   0x11FF    1000 111111111
	
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	PORTA = 0x1801; //Sending an adress.
	_delay_ms(2000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(2000);
	
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	PORTA = 0x1401; //Sending an adress.
	_delay_ms(2000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(2000);

}

int main(void)
{
	DDRE = 0b10; //Sets ALE (pin 1 on port E) as output.
	DDRA = 0xFF; //Because we read from PORTA we need to set it as an output.
	
	USART_Init(MYUBRR);
	XMEM_init();
	init_printf();
	//SRAM_test();
	
	while(1)
    {
		//exercise1();
		//exercise2();
		exercise2_bis();
    }
	return(0);
}

