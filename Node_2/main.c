#define F_CPU 4915200UL
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include can.h
#include time.h
#include uart.h

int main(void)
{
	uart_init(84000000, 9600);
	
	while(1){
	}
			
	return(0);
}
