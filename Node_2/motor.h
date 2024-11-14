#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define PWM_PERIOD 20000   
#define PWM_MAX 19000      
#define PWM_MIN 0          
#define MID_PULSE_WIDTH 1500 

void PWM_motor_init(void);
void set_PWM_duty_motor(uint16_t pulse_width);

#endif // MOTOR_H
