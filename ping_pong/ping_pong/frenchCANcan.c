#include "frenchCANcan.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//interrupt
volatile int data_pending = 0;

ISR(INT0_vect) { data_pending = 1; }

// Function to initialize CAN communication
uint8_t CAN_init(void) {
	if (mcp2515_init()) {
		printf("MCP2515 initialization failed!\n");
		return 1;
	}

	uint8_t BRP = 3;
	uint8_t BTL = 1;
	uint8_t PRSG = 1;
	uint8_t PHSG1 = 6;
	uint8_t PHSG2 = 5;

	uint8_t CNF1 = BRP;
	mcp2515_write(MCP_CNF1, &CNF1,1);

	uint8_t CNF2 = (BTL << 7) | (PHSG1 << 3) | (PRSG);
	mcp2515_write(MCP_CNF2, &CNF2 ,1);

	uint8_t CNF3 = PHSG2;
	mcp2515_write(MCP_CNF3, &CNF3,1);
	
	// Set up CAN configuration registers (e.g., bit timing, filters, etc.)
	// Example: Set normal mode (after configuration mode)
	mcp2515_modify_bit(MCP_TXB0CTRL + MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

	// enable interrupts on RXB0 and RXB1
	mcp2515_modify_bit(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT);

	// disable all transmit interrupts
	mcp2515_modify_bit(MCP_CANINTE, MCP_TX0IF | MCP_TX1IF | MCP_TX2IF, MCP_NO_INT);

	cli();

	// INT0 pin as input
	DDRD &= ~(1 << PD0);

	// INT0 pin internal pull-up
	PORTD |= (1 << PD0);

	// INT0 falling edge
	MCUCR |= 0b10;

	// INT0 external interrupt enable
	GICR |= (1 << INT0);

	sei();
	
	printf("MCP2515 initialized in normal mode\n");
	return 0;
}

// Function to send a CAN message
int CAN_send(message_t *msg) {
	
	cli();
	uint8_t status = mcp2515_read_status();
	printf("\nmsg_id: %d et status %d et  %d\n",msg->id,status,status & 0b100 | msg->length > 8);
	
	if (status & 0b100 | msg->length > 8){
		printf("test\n\n");
	return 1;
	}
	printf("test passé");
	// Load the ID and data into the correct transmit buffer of MCP2515
	uint8_t IDHIGH = (msg->id >> 3);
	uint8_t IDLOW = (msg->id << 5);
	mcp2515_write(MCP_TXB0SIDH, &IDHIGH,1);  // Standard ID high, à changer avec les << ou >> ??
	mcp2515_write(MCP_TXB0SIDL, &IDLOW,1);  // Standard ID low
	printf("\nmsg_id2: %d\n",msg->id);
	
	// Load the length of the message
	
	uint8_t total_length =(msg->length);
	mcp2515_write(MCP_TXB0DLC, &total_length,1);
	
	printf("msg_length: %d\n",msg->length);

	// Load the data
	printf("data : %d et %d",msg->data[0],msg->data[1]);
	mcp2515_write(MCP_TXB0D0, msg->data,msg->length);
	

	// Request to send the message using the RTS command
	req_to_send(MCP_RTS_TX0); // Request to send on TX buffer 0

	sei();
	return 0;
}

// Function to receive a CAN message
message_t CAN_receive() {

	//verification

	if (!data_pending){printf("data pending CAN_receive");
	}

	uint8_t status = mcp2515_read_status();
	uint8_t buffer_addr;

	if (status & MCP_RX0IF){
		buffer_addr = MCP_RXB0CTRL;
	}
	else if (status & MCP_RX1IF){
		buffer_addr = MCP_RXB1CTRL;
	}

	message_t message = {};

	uint8_t id_low = mcp2515_read(buffer_addr+0x01);
	uint8_t id_high = mcp2515_read(buffer_addr+0x02);
	message.id = id_high << 3 | (id_low & 0b11100000) >> 5;

	uint8_t lgth = mcp2515_read(buffer_addr +0x05);
	message.length = lgth; // necessaery ?& 0b1111;

	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp2515_read(buffer_addr +0x06 ); // + i neccessaire ??
	}
	return message;
}

void sendJoystickPositionCAN(uint8_t x_position, uint8_t y_position) {
	message_t msg;  // Use the correct structure defined in CAN.h
	msg.id = 1;  // Arbitrary ID, adjust based on your setup
	msg.length = 2; // 2 bytes for X and Y positions
	msg.data[0] = x_position;  // X-axis joystick value
	msg.data[1] = y_position;  // Y-axis joystick value
	
	// Send the message via the function defined in CAN.c
	CAN_send(&msg);
	
}
