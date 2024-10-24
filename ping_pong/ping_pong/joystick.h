#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JoystickDirection;

typedef struct {
	int16_t x_center;
	int16_t y_center;
} JoystickCalibration;

typedef struct {
	int16_t x_percent;
	int16_t y_percent;
	uint8_t x_percent_CAN;
	uint8_t y_percent_CAN;
} JoystickPosition;

typedef struct {
	int16_t left_percent;  // Left slider position in percentage (-100 to 100 or 0 to 100)
	int16_t right_percent; // Right slider position in percentage (-100 to 100 or 0 to 100)
} SliderPosition;

typedef struct {
	uint8_t button_left;
	uint8_t button_right;
}Buttons;

JoystickCalibration calibrateJoystick();

JoystickPosition getJoystickPosition(uint8_t adc_x, uint8_t adc_y, JoystickCalibration calib);

JoystickDirection getJoystickDirection(JoystickPosition pos);

SliderPosition getSliderPosition(uint8_t adc_left, uint8_t adc_right);

Buttons buttons_read();

#endif // JOYSTICK_H
