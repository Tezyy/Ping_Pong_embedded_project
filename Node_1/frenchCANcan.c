#include "frenchCANcan.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void can_send(message_ptr message) {
	mcp2515_write(MCP_TXB0SIDH, message->id / 8); 
	mcp2515_write(MCP_TXB0SIDL, (message->id % 8) << 5); 
	mcp2515_write(MCP_TXB0DLC, message->length);
	for (int i = 0; i < message->length; i++) {
		mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
	}

	// Request to send
	req_to_send(0);
}

message_t can_receive() {
	message_t message = {};

	uint8_t id_low = mcp2515_read(MCP_RXB0SIDL)/0b100000;
	uint8_t id_high = mcp2515_read(MCP_RXB0SIDH);
	message.id = id_high * 0b1000 + id_low;

	message.length = mcp2515_read(MCP_RXB0DLC);

	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp2515_read(MCP_RXB0D0 + i);
	}

	return message;
}
