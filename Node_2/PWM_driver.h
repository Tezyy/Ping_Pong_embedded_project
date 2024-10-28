#ifndef SERVO_H
#define SERVO_H

#include <sam.h>

// Function to configure PWM on channel 1 (PB13)
void configure_pwm_channel1(void);

void PWM_set_duty_cycle(float duty_cycle);

#endif // SERVO_H
