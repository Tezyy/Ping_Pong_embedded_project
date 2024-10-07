#include "MCP2515.h"
#include "spi.h"
#include "bit_macros.h"


#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t mcp2515_read(uint8_t adress){
	clear_bit(PORTB, PB4);

	spi_transmit(MCP_READ);
	spi_transmit(adress);
	uint8_t result = spi_receive();

	set_bit(PORTB, PB4);

	return result;

}

uint8_t mcp2515_write(uint8_t adress, uint8_t data ){
	clear_bit(PORTB, PB4);

	spi_transmit(MCP_WRITE);
	spi_transmit(adress);
	spi_transmit(data);

	set_bit(PORTB, PB4);
}

void req_to_send(uint8_t stat){
	clear_bit(PORTB, PB4);
	spi_transmit(stat);
	set_bit(PORTB, PB4);
}

uint8_t mcp2515_read_status(){
	clear_bit(PORTB, PB4);
	spi_transmit(MCP_READ_STATUS);
	uint8_t result = spi_receive();
	set_bit(PORTB, PB4);
	return result;
}

void mcp2515_modify_bit(uint8_t address, uint8_t mask, uint8_t data){
	clear_bit(PORTB, PB4);
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	set_bit(PORTB, PB4);
}

void mcp2515_reset(){
	clear_bit(PORTB, PB4);
	spi_transmit(MCP_RESET);
	set_bit(PORTB, PB4);
}

uint8_t mcp2515_init ()
{
	uint8_t value ;
	init_spi() ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	// Self - test
	mcp2515_write( MCP_CANSTAT , & value );
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
	}
	// More initialization
	return 0;
}
