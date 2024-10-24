#ifndef FRENCHCANCAN_H_
#define FRENCHCANCAN_H_

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>

// Send-buffer 0
#define MCP_TXB0SIDH 0x31 //0b0011 0001
#define MCP_TXB0SIDL 0x32 //0b0011 0010
#define MCP_TXB0EID8 0x33
#define MCP_TXB0EID0 0x34
#define MCP_TXB0DLC 0x35 //0b0011 0101
#define MCP_TXB0D0 0x36 //0b0011 0110
#define MCP_TXB0D1 0x37
#define MCP_TXB0D2 0x38
#define MCP_TXB0D3 0x39
#define MCP_TXB0D4 0x3A
#define MCP_TXB0D5 0x3B
#define MCP_TXB0D6 0x3C
#define MCP_TXB0D7 0x3D
// Send-buffer 0
#define MCP_TXB0SIDH 0x31
#define MCP_TXB0SIDL 0x32
#define MCP_TXB0DLC 0x35
#define MCP_TXB0D0 0x36

// Motta-buffer 0
#define MCP_RXB0SIDH 0x61
#define MCP_RXB0SIDL 0x62
#define MCP_RXB0DLC 0x65
#define MCP_RXB0D0 0x66

// CAN message structure
typedef struct Message {
	uint8_t id;
	uint8_t length;
	uint8_t data[8];
} message_t;

uint8_t CAN_init(void);
int CAN_send(message_t *msg);
message_t CAN_receive();
void sendJoystickPositionCAN(uint8_t x_position, uint8_t y_position);

#endif /* FRENCHCANCAN_H_ */
