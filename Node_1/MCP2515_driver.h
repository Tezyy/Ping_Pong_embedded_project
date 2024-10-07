#ifndef MCP2515_DRIVER_H
#define MCP2515_DRIVER_H

#define F_CPU 4915200UL
#include <util/delay.h>

uint8_t mcp2515_read(uint8_t adress);

uint8_t mcp2515_write(uint8_t adress, uint8_t data );

void req_to_send(uint8_t stat);

uint8_t mcp2515_read_status();

void mcp2515_modify_bit(uint8_t address, uint8_t mask, uint8_t data);

void mcp2515_reset();

uint8_t mcp2515_init();

#endif
