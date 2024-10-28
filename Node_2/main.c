#include "can.h"
#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Import UART from Node 2 starter code, then edit include path accordingly.
// Also, remember to update the makefile
#include "uart.h"
#include "servo.h"

#define F_CPU 84000000
#define BAUDRATE 9600

CanInit_t bit_timing = {.phase2 = 5, .propag = 1, .phase1 = 6, .sjw = 0, .brp = 41, .smp = 0};

CanMsg receive_can;


int main()
{
	SystemInit();
	PWM_init();   // Initialize PWM

	WDT->WDT_MR = WDT_MR_WDDIS; // Disable Watchdog Timer

	//PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
	//PIOB->PIO_OER = PI_PB13; //Configure PB13 as an output
	
	uart_init(F_CPU, BAUDRATE);
	can_init(bit_timing, 0);


	while (1)
	{
		while (can_rx(&receive_can)){
			printf("Receiving");
			can_printmsg(receive_can);
			}
		set_PWM_duty(1500);
	
	}
}
