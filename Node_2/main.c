#include "can.h"
#include "PWM_driver.h"
#include "time.h"
#include "adc.h"

#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Import UART from Node 2 starter code, then edit include path accordingly.
// Also, remember to update the makefile
#include "uart.h"


#define F_CPU 84000000
#define BAUDRATE 9600

CanInit_t bit_timing = {.phase2 = 5, .propag = 1, .phase1 = 6, .sjw = 0, .brp = 41, .smp = 0};

CanMsg receive_can;

uint16_t pwm_duty_joystick ;
uint32_t adc_value ;


int main()
{
	SystemInit();
	PWM_init();   // Initialize PWM

	//WDT->WDT_MR = WDT_MR_WDDIS; // Disable Watchdog Timer

	//PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
	//PIOB->PIO_OER = PI_PB13; //Configure PB13 as an output
	
	uart_init(F_CPU, BAUDRATE);
	can_init(bit_timing, 0);

	time_init();
	adc_init();
	while (1)
	{
		if(can_rx(&receive_can)){
			//printf("Receiving");
			//can_printmsg(receive_can);
			//printf("byte 1 : %d\n", (receive_can.byte[1]-128));
			//pwm_duty_joystick=PWM_value((receive_can.byte[0]-128));
			//printf("pwm_duty_joystick : %d\n\n", pwm_duty_joystick);
			set_PWM_duty(PWM_value((receive_can.byte[0]-128)));
			}
		//set_PWM_duty(2000);
		adc_value=adc_read();
		printf("adc value adr0 : %d\n", adc_value);
	
	}
}
