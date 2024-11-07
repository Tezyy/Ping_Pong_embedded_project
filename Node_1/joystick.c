#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "joystick.h"
#include "adc.h"

#define THRESHOLD 0

JoystickCalibration calibrateJoystick() {
	JoystickCalibration calib;

	adc_data_t adc_inputs = adc_read();

	calib.x_center = adc_inputs.joystick_x;
	calib.y_center = adc_inputs.joystick_y;

	return calib;
}

JoystickPosition getJoystickPosition(uint8_t adc_x, uint8_t adc_y, JoystickCalibration calib) { 
	JoystickPosition pos;
	
	// Convert ADC value to percentage for X-axis
	pos.x_percent = ((int16_t)adc_x - calib.x_center) * 100 / calib.x_center;
	pos.x_percent_CAN=(uint8_t)(pos.x_percent + 128);
		
	// Convert ADC value to percentage for Y-axis
	pos.y_percent = ((int16_t)adc_y - calib.y_center) * 100 / calib.y_center;
	pos.y_percent_CAN=(uint8_t)(pos.y_percent + 128);
	
	return pos;
}

JoystickDirection getJoystickDirection(JoystickPosition pos) {
	if (pos.x_percent > THRESHOLD+15) {
		return RIGHT;
	}
	else if (pos.x_percent < THRESHOLD-15) {
		return LEFT;
	}
	else if (pos.y_percent > THRESHOLD+15) {
		return UP;
	}
	else if (pos.y_percent < THRESHOLD-15) {
		return DOWN;
	}
	else {
		return NEUTRAL;
	}
}

SliderPosition getSliderPosition(uint8_t adc_left, uint8_t adc_right) {
	SliderPosition pos;

	// Convert the ADC values to percentages
	pos.left_percent = (int16_t)(adc_left * 100) / 255;   // Range: 0 to 100%
	pos.right_percent = (int16_t)(adc_right * 100) / 255;

	return pos;
}

Buttons buttons_read(){
	Buttons buttons;
	buttons.button_right = ((PINB & (1<<PB0)) != 0);
	buttons.button_left = ((PINB & (1<<PB1)) != 0);
	return buttons;
}
