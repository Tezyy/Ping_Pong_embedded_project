#ifndef XMEM_SRAM_H
#define XMEM_SRAM_H

// Define CPU clock speed
#define F_CPU 4915200UL

// AVR standard includes
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void XMEM_init(void);
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);
void SRAM_test(void);

#endif // XMEM_SRAM_H
