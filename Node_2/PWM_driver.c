#include "PWM_driver.h"
#include <sam.h>

#define PWM_PERIOD 20000      // PWM period in microseconds (20 ms)
#define MIN_PULSE_WIDTH 900   // Minimum pulse width in microseconds (0.9 ms)
#define MAX_PULSE_WIDTH 2100  // Maximum pulse width in microseconds (2.1 ms)
#define MID_PULSE_WIDTH 1500  // Middle/Neutral pulse width in microseconds (1.5 ms)
#define PWM_CHANNEL 1         // Use PWM channel 1
#define PB13_PIN 13           // PB13 corresponds to pin 13

void PWM_init() {
	
	// Enable PIOB and PWM peripheral clocks
    PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
    PMC->PMC_PCER1 |= (1 << (ID_PWM - 32));  // Enable clock for PWM

    // Configure PIOB pin 13 (PB13) for PWM output
    PIOB->PIO_PDR |= PIO_PDR_P13;    // Disable PIO control for PB13 (peripheral control)
    PIOB->PIO_ABSR |= PIO_ABSR_P13;  // Select peripheral B for PB13 (PWM functionality)

	// Set the PWM clock (PWM_CLK is MCK divided by a prescaler)
	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); 
	/*PWM_CLK_PREA(0): Selects Clock A without any prescaling.
	PWM_CLK_DIVA(84): Divides the 84 MHz master clock by 84 to get 1 MHz for the PWM clock.
	
	This 1 MHz PWM clock means that each clock cycle represents 1 microsecond,
	making it easy to handle pulse widths for the servo,
	as you can directly set the pulse width in microseconds (e.g., 1500 for 1.5 ms).*/

	// Configure PWM channel
	PWM->PWM_SCM = PWM_SCM_UPDM_MODE0;
	
	PWM->PWM_CH_NUM[PWM_CHANNEL].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;  // Use Clock A with inverted polarity
	PWM->PWM_CH_NUM[PWM_CHANNEL].PWM_CPRD = PWM_PERIOD;        // Set period to 20 ms (20000 us)
	PWM->PWM_CH_NUM[PWM_CHANNEL].PWM_CDTY = MID_PULSE_WIDTH;   // Start with the mid-point pulse (1.5 ms)

	// Enable the PWM channel
	PWM->PWM_ENA = (1 << PWM_CHANNEL);
}

//pulse_width takes wetween 900 and 2100
void set_PWM_duty(uint16_t pulse_width) { //change of uint16_t with float
	
	// Safety check: limit pulse width to the servo's valid range
	if (pulse_width < MIN_PULSE_WIDTH) {
		pulse_width = MIN_PULSE_WIDTH;  // Clamp to minimum
		}
		
	else if (pulse_width > MAX_PULSE_WIDTH) {
		pulse_width = MAX_PULSE_WIDTH;  // Clamp to maximum
		}

	// Set the new duty cycle (pulse width)
	PWM->PWM_CH_NUM[PWM_CHANNEL].PWM_CDTYUPD = pulse_width;
    PWM->PWM_SCUC = PWM_SCUC_UPDULOCK; //update at the new clock cycle
}

// -180< INPUT <180
uint16_t PWM_value(int8_t input_joystick){
	uint16_t result =0;
	//check if not too big
	if (input_joystick < -110) input_joystick =-110;
	else if (input_joystick > 110) input_joystick = 110;
	else if (input_joystick > -50 && input_joystick < 50) input_joystick = 0;
	
	if (input_joystick >0) input_joystick = input_joystick/0.72; //change of base because value max of x=72
	else if (input_joystick < 0) input_joystick = input_joystick/1.26;
	else input_joystick = 0;
	
	input_joystick = input_joystick/1.1;
	result=(uint16_t)(-5.9*(input_joystick) +1500);

	return result;
}
