#ifndef ADC_H
#define ADC_H

#include <stdint.h> 
#define NUMBER_OF_CHANNELS 4

#define F_CPU 4915200UL

typedef struct {
	uint8_t joystick_x;
	uint8_t joystick_y;
	uint8_t slider_left;
	uint8_t slider_right;
} adc_data_t;

void adc_init(void);
adc_data_t adc_read();

#endif // ADC_H
