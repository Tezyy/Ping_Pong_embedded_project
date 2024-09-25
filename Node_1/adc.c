#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>

#include "adc.h"

void adc_init(){
	DDRD |= (1 << DDD5); //set PD5 to output
	
	// fast PWM mode
	TCCR1A |= (1<<WGM10) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	
	//toggle
	TCCR1A &= ~(1<<COM1A1);
	TCCR1A |= (1<<COM1A0);
	
	//clock select bit
	TCCR1B &= ~(1<<CS12);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS10);
	
	//Had to be zero
	TCCR1A &= ~(1<<FOC1A);
	
	OCR1AH=0x0;
	OCR1AL=0x1;
	
	DDRD &= ~(1<<DDD4); //set PD4 to input
	 
}


uint8_t adc_read(uint8_t channel){
	volatile char* ext_mem = (char *)0x1400; //base address for adc
	ext_mem[0] = 0;

	// wait for end of conversion
	_delay_ms(9*NUMBER_OF_CHANNELS*2 / F_CPU); //do we have to put number_of_channels=4 somewhere ? I think so

	// read desired channel
	uint8_t data;

	for (int i = 0; i <= channel; ++i) {
		data = ext_mem[0];
	}
	
	return data;
}

uint8_t adc_read(uint8_t channel); //volatile
pos_calibrate();
pos_t pos_read(void);
