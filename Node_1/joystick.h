#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h> 

typedef struct {
	uint8_t x_percent; 
	uint8_t y_percent; 
} JoystickPosition;

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JoystickDirection;

#define ADC_MIN 0
#define ADC_MAX 255
#define JOYSTICK_CENTER 128 

#define THRESHOLD 30

JoystickPosition getJoystickPosition(uint8_t adc_x, uint8_t adc_y);

JoystickDirection getJoystickDirection(JoystickPosition pos);

#endif // JOYSTICK_H
