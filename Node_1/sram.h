#ifndef XMEM_H
#define XMEM_H

// Define CPU clock frequency
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <avr/io.h>  // For MCUCR, SFIOR, etc.
#include <stdio.h>   // For printf
#include <stdlib.h>  // For rand, srand
#include <stdint.h>  // For standard integer types like uint8_t, uint16_t


// Define base address for external memory
#define BASE_ADDRESS_SRAM 0x1800
#define LED_PORT     0x0800

// Function Prototypes
void XMEM_init(void);
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);
void SRAM_test(void);

#endif // XMEM_H
