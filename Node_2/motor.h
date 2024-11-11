#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

// PWM configuration constants
#define PWM_PERIOD 20000    // PWM period in microseconds (20 ms)
#define PWM_MAX 19000      // Maximum pulse width
#define PWM_MIN 0           // Minimum pulse width
#define MID_PULSE_WIDTH 1500 // Middle pulse width, often around 1.5 ms for a servo at center position

// Function prototypes
void PWM_motor_init(void);
void set_PWM_duty_motor(uint16_t pulse_width);
uint16_t PWM_value_motor(int8_t input_joystick);
uint16_t wanted_encoder_position(uint8_t joystick_x);
void stop_motor();
uint16_t control_motor_to_position(uint16_t current_position, uint16_t wanted_position);
void set_motor_position(uint16_t current_position, uint16_t wanted_position);
void set_motor_left();

#endif // MOTOR_H
