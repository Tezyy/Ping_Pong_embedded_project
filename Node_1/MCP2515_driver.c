#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "spi.h"
#include "bit_macros.h"

#define F_CPU 4915200UL
#include <util/delay.h>
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
	init_spi() ; // Initialize SPI
	mcp2515_reset () ; // Send reset - command
	_delay_ms(1);
	// Self - test
	uint8_t value = mcp2515_read( MCP_CANSTAT);
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
	}
	// ce qui vient après là, c'est pour le node 2, je suis pas certaine à 10 000% attention mais mes calculs ont donné ça
	// CNF1: Configure Baud Rate Prescaler (BRP) and SJW (Synchronization Jump Width)
    MCP2515_write(CNF1, (1 << BRP0) | (0 << SJW0));  // BRP = 1 (div par 2), SJW = 1

    // CNF2: Configure Phase Segment 1 (PHSEG1) and Propagation Segment (PRSEG)
    MCP2515_write(CNF2, (3 << PRSEG0)   // Propagation Segment = 1 TQ (valeur 0)
                        | (3 << PHSEG10)  // Phase1 = 4 TQ (valeur 3 correspond à 4 TQ)
                        | (1 << BTLMODE)); // Mode pour que Phase2 soit déterminé par CNF3

    // CNF3: Configure Phase Segment 2 (PHSEG2)
    MCP2515_write(CNF3, (2 << PHSEG20));  // Phase2 = 3 TQ (valeur 2)
	
	return 0;
}
