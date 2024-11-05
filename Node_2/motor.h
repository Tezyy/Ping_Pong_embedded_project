#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <sam.h>
#include <stdint.h>
#include "can.h"
#include "PWM_driver.h"

// Constants for joystick configuration
#define JOYSTICK_MID      128         // Midpoint for joystick (assuming 8-bit resolution)
#define JOYSTICK_THRESHOLD 10          // Threshold to determine motor direction

// Function prototypes
void configure_motor_driver(void);
void control_motor_with_joystick(CanMsg *receive_can);

// Optionally, you can declare any global variables or types needed
uint16_t pwm_duty_joystick; // Variable to hold PWM duty cycle based on joystick position

#endif // MOTOR_DRIVER_H
