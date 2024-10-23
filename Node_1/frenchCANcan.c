#include "frenchCANcan.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Function to initialize CAN communication
uint8_t CAN_init(void) {
	if (mcp2515_init()) {
		printf("MCP2515 initialization failed!\n");
		return 1;
	}
	
	// Set up CAN configuration registers (e.g., bit timing, filters, etc.)
	// Example: Set normal mode (after configuration mode)
	mcp2515_modify_bit(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	printf("MCP2515 initialized in normal mode\n");
	return 0;
}

// Function to send a CAN message
void CAN_send(message_t *msg) {
	// Load the ID and data into the correct transmit buffer of MCP2515
	mcp2515_write(MCP_TXB0SIDH, (uint8_t)(msg->id /8));  // Standard ID high, à changer avec les << ou >> ??
	mcp2515_write(MCP_TXB0SIDL, (uint8_t)((msg->id %8)<< 5));  // Standard ID low

	// Load the length of the message (DLC)
	mcp2515_write(MCP_TXB0DLC, msg->length);

	// Load the data
	for (uint8_t i = 0; i < msg->length; i++) {
		mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);
	}

	// Request to send the message using the RTS command
	req_to_send(MCP_RTS_TX0); // Request to send on TX buffer 0
}

// Function to receive a CAN message
message_t CAN_receive() {

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

void sendJoystickPositionCAN(uint8_t x_position, uint8_t y_position) {
	message_t msg;  // Use the correct structure defined in CAN.h
	msg.id = (unsigned int) 0x01;  // Arbitrary ID, adjust based on your setup
	msg.length = 2; // 2 bytes for X and Y positions
	msg.data[0] = x_position;  // X-axis joystick value
	msg.data[1] = y_position;  // Y-axis joystick value
	
	// Send the message via the function defined in CAN.c
	CAN_send(&msg);

}
