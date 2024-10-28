#ifndef PWM_H
#define PWM_H

#include <stdint.h>  // For standard integer types

// Define PWM period and pulse width limits in microseconds
#define PWM_PERIOD      20000    // PWM period in microseconds (20 ms)
#define MIN_PULSE_WIDTH 900      // Minimum pulse width in microseconds (0.9 ms)
#define MAX_PULSE_WIDTH 2100     // Maximum pulse width in microseconds (2.1 ms)
#define MID_PULSE_WIDTH 1500     // Middle/Neutral pulse width in microseconds (1.5 ms)

// Define the PWM channel and PB13 pin used for the servo control
#define PWM_CHANNEL 1           // Use PWM channel 1
#define PB13_PIN 13             // PB13 corresponds to pin 13

/**
 * @brief Initializes the PWM module and configures PB13 as the PWM output for servo control.
 */
void PWM_init(void);

/**
 * @brief Sets the PWM duty cycle (pulse width) for servo control.
 *
 * @param pulse_width The desired pulse width in microseconds (0.9 ms - 2.1 ms).
 *                    If the pulse width is outside the valid range, it will be clamped
 *                    to the closest valid value.
 */
void set_PWM_duty(uint16_t pulse_width);

#endif /* PWM_H */

