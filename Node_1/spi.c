#include "spi.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void init_spi(){
	DDRB |= (1<<PB5) | (1<<PB7) | (1<<PB4); //MOSI(PB5) SCK(PB7) SS(PB4) output
	DDRB &= ~(1 << PB6); // MISO (PB6) input
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); // enable SPI, set SPI mode 0, set SCK rate to F_CPU/ 16
}

uint8_t spi_data(uint8_t data)
{
    // start transmission
    SPDR = data;
    // wait for transmission complete
    while (!(SPSR & (1 << SPIF)))
    ;

    // return data register
    return SPDR;
}
