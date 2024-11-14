#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <stdint.h>

void init_spi(void);
uint8_t spi_data(uint8_t data);

#endif // SPI_H


