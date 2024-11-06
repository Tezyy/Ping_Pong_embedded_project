#include "can.h"
#include "PWM_driver.h"
#include "time.h"
#include "adc.h"
#include "timer_score.h"
#include "uart.h"

#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define F_CPU 84000000
#define BAUDRATE 9600
#define ID_GAME_START 11
#define ID_JOYSTICK 12
#define ID_BUTTON_RIGHT 13

CanInit_t bit_timing = {.phase2 = 5, .propag = 1, .phase1 = 6, .sjw = 0, .brp = 41, .smp = 0};

CanMsg receive_can;

uint16_t pwm_duty_joystick ;
uint32_t adc_value ;
static uint64_t score = 0;
Time SCORE_final =(Time){.hours = 0, .minutes = 0, .seconds = 0, .msecs = 0};
//extern int score = 0;
static uint8_t button_state = 0;
static uint8_t game_start = 0; //0 if the game is not started, 1 if it is
static uint8_t game_running =0;
static uint8_t game_end =0;
int main()
{
	SystemInit();
	PWM_init();   // Initialize PWM

	WDT->WDT_MR = WDT_MR_WDDIS; // Disable Watchdog Timer

	//PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
	//PIOB->PIO_OER = PI_PB13; //Configure PB13 as an output
	
	uart_init(F_CPU, BAUDRATE);
	can_init(bit_timing, 0);

	time_init();
	adc_init();
	//score = time_now();
	while (1)
	{
		if ((game_running !=1) && (game_end !=1)){
		printf("en attente du joueur...\r\n");
		}
		if(can_rx(&receive_can)){
			//printf("message id %d\r\n", receive_can.id);
			if (receive_can.id == 11) {
				
				reset_score_timer();
				start_score_timer();
				printf("game running...");
				game_start=1;
				game_running=1;
				
				//all initialization for the game to start properly
			}
		}
		//printf("game running %u\r\n", game_running);
		
		if (game_running !=0){
			can_rx(&receive_can);
			
			switch (receive_can.id){
				case ID_JOYSTICK :
					//printf("id joystick");
					set_PWM_duty(PWM_value((receive_can.byte[0]-128)));
					break;
				case ID_BUTTON_RIGHT :
					button_state = receive_can.byte[0];
					printf("test button state : %u\r\n",button_state);
					break;
			}
			adc_value=adc_read();
			if (adc_value <500){
				printf("adc value %u", adc_value);
				score =stop_score_timer();
				printf("SCORE %f seconds \r\n",totalSeconds(score));
				game_running=0;
				game_end =1;
				
			}
			
		}
		if (game_end !=0){
			printf("TU AS PERDU...");
		}
		
// 		printf("adc value adr0 : %d\r\n", score);
// 		
		
	}
	
}
