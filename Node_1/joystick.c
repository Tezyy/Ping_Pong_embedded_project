#include <stdint.h>

#include "joystick.h"

typedef struct {
	uint8_t x_percent; // X-axis position in percentage (-100 to 100)
	uint8_t y_percent; // Y-axis position in percentage (-100 to 100)
} JoystickPosition;


typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JoystickDirection;


#define ADC_MIN 0
#define ADC_MAX 255 //because 8 bits 
#define JOYSTICK_CENTER 128 // Assuming 128 is the center value (255/2 = 127.5 in reality but idk if I can write this value)

JoystickPosition getJoystickPosition(uint16_t adc_x, uint16_t adc_y) { // uint16_t to have range from -100% to +100%
	JoystickPosition pos;
	
	// Convert ADC value to percentage for X-axis
	pos.x_percent = ((uint16_t)(adc_x - JOYSTICK_CENTER) * 100) / (JOYSTICK_CENTER);
	
	// Convert ADC value to percentage for Y-axis
	pos.y_percent = ((uint16_t)(adc_y - JOYSTICK_CENTER) * 100) / (JOYSTICK_CENTER);
	
	return pos;
}

#define THRESHOLD 30  // Define a threshold for the joystick direction, typically around 10-20% of the full ADC range

JoystickDirection getJoystickDirection(JoystickPosition pos) {
	if (pos.x_percent > THRESHOLD) {
		return RIGHT;
	}
	else if (pos.x_percent < -THRESHOLD) {
		return LEFT;
	}
	else if (pos.y_percent > THRESHOLD) {
		return UP;
	}
	else if (pos.y_percent < -THRESHOLD) {
		return DOWN;
	}
	else {
		return NEUTRAL;
	}
}
