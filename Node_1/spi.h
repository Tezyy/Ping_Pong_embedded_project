#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <stdint.h>

void init_spi(void);
void spi_transmit(uint8_t data);
uint8_t spi_receive(void);
void spi_select_slave(void);
void spi_deselect_slave(void);

#endif // SPI_H

