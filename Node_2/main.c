#include "can.h"
#include "PWM_driver.h"
#include "time.h"
#include "adc.h"
#include "game.h"
#include "timer_score.h"
#include "uart.h"
#include "motor.h"
#include "encoder.h"
#include "PI.h"

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
static uint8_t button_state = 0;
static uint8_t game_start = 0; //0 if the game is not started, 1 if it is
static uint8_t game_running =0;
static uint8_t game_end =0;

int main()
{
	SystemInit();
	PWM_init();   // Initialize PWM

	WDT->WDT_MR = WDT_MR_WDDIS; // Disable Watchdog Timer
	
	uart_init(F_CPU, BAUDRATE);
	can_init(bit_timing, 0);

	time_init();
	adc_init();
	init_TC2_quadrature_mode();
	PWM_motor_init();
	game_init();
	while (1)
	{
		if ((game_running !=1) && (game_end !=1)){
		printf("waiting for player...\r\n");
		printf("_______________________\r\n");
		set_PWM_duty_motor(0);
		set_PWM_duty(0);
		}
		if(can_rx(&receive_can)){ // && game_running !=1
			if (receive_can.id == 11) {
				
				//all initialization for the game to start properly
				reset_score_timer();
				start_score_timer();
				printf("game running...");
				game_start=1;
				game_running=1;
			}
		}
		
		if (game_running !=0){
			can_rx(&receive_can);
			
			switch (receive_can.id){
				case ID_JOYSTICK :
					set_PWM_duty(PWM_value((receive_can.byte[1]-128))); //servo
					
					int16_t encoder_position = read_encoder_position();
					
					//Joystick moteur
					int16_t u = PI(receive_can.byte[0],encoder_position);
					u = u*5;
					printf("u=%d\n\r", u);
					if (u>0){
						PIOC->PIO_CODR = PIO_PC23;
						set_PWM_duty_motor(u);
					}
					else if (u<0){
						PIOC->PIO_SODR = PIO_PC23;
						u = abs(u);
						set_PWM_duty_motor(u);
					}

					solenoid (0);
					
					break;
					
				case ID_BUTTON_RIGHT :
					button_state = receive_can.byte[0];
					printf("test button state : %u\r\n",button_state);
					solenoid(1);
					solenoid(0);
					break;
				
			}
			adc_value=adc_read();
			if (adc_value <500){
				printf("adc value %u", adc_value);
				score =stop_score_timer();
				printf("SCORE %f seconds \r\n",totalSeconds(score));
				game_running=0;
				game_end =0;			
			}		
		}	
	}
}
