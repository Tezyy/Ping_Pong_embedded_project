#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "adc.h"
#include "sram.h"

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

adc_data_t adc_read()
{
	volatile char *adc_start_address = (char *) 0x1400; //0x1400 is the first adress in the adress space.
	adc_data_t adc_inputs;

	adc_start_address[0] = 0x00; //Write any value just to send write signal to ADC.

	//For read and write, the adress does not matter as long as it is within the ADC adress space
	//The order of reads matters here, as the ADC inputs are stored in the ADC's RAM in a certain order (Pin 0 -> Pin 3).
	//Reading "pops" values from the RAM in FIFO order.
	adc_inputs.joystick_x = adc_start_address[0]; //canal 0
	adc_inputs.joystick_y = adc_start_address[0]; //canal 1
	adc_inputs.slider_left=adc_start_address[0]; //canal 2
	adc_inputs.slider_right=adc_start_address[0]; //canal 3 
	
	return adc_inputs;
}
