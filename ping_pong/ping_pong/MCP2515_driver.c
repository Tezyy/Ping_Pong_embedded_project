#include "MCP2515.h"
#include "spi.h"
#include "bit_macros.h"

#define F_CPU 4915200UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t mcp2515_read(uint8_t adress, uint8_t *data_buffer, int buffer_size){
	clear_bit(PORTB, PB4);

	spi_data(MCP_READ);
	spi_data(adress);
	for (int i = 0; i < buffer_size; i++)
	uint8_t data_buffer[i] = spi_data(0X00);

	set_bit(PORTB, PB4);

	return result;

}

// void MCP2515_read(uint8_t addr, uint8_t *data_buffer, int buffer_size)
// {
//     clear_bit(PORTB, PB4);

//     spi_data(MCP_READ);

//     spi_data(addr);

//     for (int i = 0; i < buffer_size; i++)
//     data_buffer[i] = spi_data(DONT_CARE);

//     clear_bit(PORTB, PB4);
// }

uint8_t mcp2515_write(uint8_t adress, uint8_t *data, uint8_t buffer_size ){
	clear_bit(PORTB, PB4);
	
	spi_data(MCP_WRITE);

	spi_data(adress);

	for (int i = 0; i < buffer_size; i++){
	spi_data(data[i]);
	printf("\nin mcp2515 : %d\n",data[i]);
	}
	set_bit(PORTB, PB4);
}

void req_to_send(uint8_t stat){
	clear_bit(PORTB, PB4);
	spi_data(stat);
	set_bit(PORTB, PB4);
}

uint8_t mcp2515_read_status(){
	clear_bit(PORTB, PB4);
	spi_data(MCP_READ_STATUS);
	uint8_t result = spi_data(0X00);
	set_bit(PORTB, PB4);
	return result;
}

void mcp2515_modify_bit(uint8_t address, uint8_t mask, uint8_t data){
	clear_bit(PORTB, PB4);
	spi_data(MCP_BITMOD);
	spi_data(address);
	spi_data(mask);
	spi_data(data);
	set_bit(PORTB, PB4);
}

void mcp2515_reset(){
	clear_bit(PORTB, PB4);
	spi_data(MCP_RESET);
	set_bit(PORTB, PB4);
}

uint8_t mcp2515_init ()
{
	init_spi() ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	_delay_ms(1);
	// Self - test
	uint8_t value = mcp2515_read( MCP_CANSTAT);
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
		} else {
		return 0;
	}
}
