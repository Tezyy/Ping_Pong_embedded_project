#include <sam.h>
#include "encoder.h"
#include "motor.h"
#include "can.h"

#define KP 1.0       // Proportional gain
#define KI 0.1       // Integral gain
#define PWM_MAX 19000
#define PWM_MIN 0

// Global variables for PI controller
float integral_sum = 0;  // Integral accumulator

// Function to calculate the PI control output
int16_t calculate_PI_output(uint16_t current_position, uint16_t target_position) {
    // Calculate the error
    int16_t error = target_position - current_position;
    
    // Proportional term
    float proportional = KP * error;
    
    // Integral term
    integral_sum += error;
    float integral = KI * integral_sum;
    
    // Total output
    int16_t output = proportional + integral;
    
    // Limit the output to the allowable PWM range
    if (output > PWM_MAX) {
        output = PWM_MAX;
        integral_sum -= error;  // Prevent integral windup
    } else if (output < PWM_MIN) {
        output = PWM_MIN;
        integral_sum -= error;  // Prevent integral windup
    }

    return output;
}

//et apres dans le main :
// Read current encoder position
        uint16_t current_position = read_encoder_position();
        
        // Read target position from joystick
        uint16_t target_position = receive_can.byte[0]; //et ouais mais non à modifier ça en fct des valeurs de l'encodeur
        
        // Calculate PI control output
        int16_t pwm_output = calculate_PI_output(current_position, target_position);
        
        // Set motor PWM
        set_motor_pwm(pwm_output);
