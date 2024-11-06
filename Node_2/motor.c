// #include <sam.h>
// #include <stdarg.h>
// #include <stdio.h>
// #include <string.h>

// #include "can.h"
// #include "PWM_driver.h"
// #include "motor.h"

// // Initialize motor driver pins and PWM
// void configure_motor_driver(void) {
// 	// Configuration de la broche PHASE pour le contrôle de direction
// 	PMC->PMC_PCER0 |= (1 << ID_PIOB);     // Enable clock for PIOB
// 	PIOB->PIO_OER = PIO_PB13;             // Configure PB13 as output (PHASE)
// 	PWM_init();                           // Initialize PWM for ENABLE
// }

// void control_motor_with_joystick(CanMsg *receive_can) {
// 	int8_t joystick_x = (int8_t)(receive_can->byte[0] - JOYSTICK_MID); // Center joystick at 0

// 	// Set motor direction based on joystick position
// 	if (joystick_x > JOYSTICK_THRESHOLD) {
// 		PIOB->PIO_SODR = PIO_PB13;  // Forward direction (PHASE = 1)
// 		} else if (joystick_x < -JOYSTICK_THRESHOLD) {
// 		PIOB->PIO_CODR = PIO_PB13;  // Reverse direction (PHASE = 0)
// 		} else {
// 		// Neutral position: stop motor by setting PWM duty cycle to 0
// 		set_PWM_duty(0);
// 		//return;
// 	}

// 	// Calculate and set PWM duty cycle based on joystick position
// 	uint16_t pwm_duty_joystick = PWM_value(abs(joystick_x));  // Adjust PWM based on joystick position
// 	set_PWM_duty(pwm_duty_joystick);
// }
