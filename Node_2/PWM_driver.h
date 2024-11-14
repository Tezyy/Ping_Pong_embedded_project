#ifndef PWM_H
#define PWM_H

#include <stdint.h>  // For standard integer types

// Define PWM period and pulse width limits in microseconds
#define PWM_PERIOD      20000    // PWM period in microseconds (20 ms)
#define MIN_PULSE_WIDTH 900      // Minimum pulse width in microseconds (0.9 ms)
#define MAX_PULSE_WIDTH 2100     // Maximum pulse width in microseconds (2.1 ms)
#define MID_PULSE_WIDTH 1500     // Middle/Neutral pulse width in microseconds (1.5 ms)
#define PWM_CHANNEL 1           // Use PWM channel 1
#define PB13_PIN 13             // PB13 corresponds to pin 13

void PWM_init(void);
void set_PWM_duty(uint16_t pulse_width);
uint16_t PWM_value(int8_t input_joystick);

#endif /* PWM_H */

