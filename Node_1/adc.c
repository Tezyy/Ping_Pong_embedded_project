#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>

#include "sram.h"

#define BASE_ADDRESS_ADC 0x1400

//fonctions à coder selon lab lecture 2
adc_init (void);
uint8_t adc_read(uint8_t channel); //volatile
pos_calibrate();
pos_t pos_read(void);
