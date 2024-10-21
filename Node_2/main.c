#define F_CPU 84000000UL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sam.h>

#include "servo.h"
#include "uart.h"


int main(void)
{
	SystemInit(); // Initialize the system
	//configure_pwm_channel1(); // Configure PWM on channel 1

	uart_init(84000000, 9600);
	can_init(/*Adjust this value for CAN bus timing (based on system clock and bus requirements)*/, 0); // 0 for no RX interrupt/1 for RX interrupt

	CanMsg received_msg;
	
	while(1){
		//printf("Hello");
		// Check if a CAN message has been received
        	if (can_rx(&received_msg)) {
           		// Print the received message
           		can_printmsg(received_msg);

		//Joystick x and y are stored in the first two bytes of the CAN message
        		uint8_t joystick_x = received_msg.byte[0];
       			uint8_t joystick_y = received_msg.byte[1];
			printf("Received Joystick Coordinates - X: %d%%, Y: %d%%\n", joystick_x, joystick_y);
		}	
	}
	
	return(0);
}
