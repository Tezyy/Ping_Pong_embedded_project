#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "encoder.h"
#include "time.h"

#define Kp 1
#define Ki 0.8
#define T 0.001 
#define ENCODER_MAX 5300
#define ENCODER_MIN 0

//at the beginning, when we send the code to the Atmel the motor goes all to the right
//and the encoder is reset, so the all to the right position corresponds to 0 on the encoder
//and when we go to the left the encoder max value is around 5300

int16_t integral = 0;
int16_t output_control = 0;


int16_t PI(uint16_t target_position, int16_t current_position){ //current_position = position de l'encoder (0-5300) and target_position = position du joystick (0-255)
	
	if(integral > 4000){		//anti windup, we limit the integral term in case the integral term has accumulated a large enough value that it continues to influence the control output even after reaching the target
		integral = 2000;
	}
	else if (integral < -4000){
		integral = -2000;
		}
	
	float f_scaled_target_position = target_position*5500/170;
	int16_t scaled_target_position = (int16_t)f_scaled_target_position;
		
	int16_t error = scaled_target_position - current_position;
	
	integral += error;

	output_control = Kp*error + Ki*integral*T;
	
	return output_control;
}





