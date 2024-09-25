#ifndef ADC_H
#define ADC_H

#include <stdint.h> 
#define NUMBER_OF_CHANNELS 4

#define F_CPU 4915200UL

void adc_init(void);
uint8_t adc_read(uint8_t channel);

#endif // ADC_H
