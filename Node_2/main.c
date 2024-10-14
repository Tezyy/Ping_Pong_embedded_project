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
	
	while(1){
		printf("Hello");
	}
	
	return(0);
}
