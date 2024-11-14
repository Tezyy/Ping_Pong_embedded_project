#include "motor.h"
#include <sam.h>

#define PWM_PERIOD 20000			// PWM period in microseconds (20 ms)
#define PWM_MAX 19000				//PWM max
#define PWM_MIN 0					//PWM min
#define MID_PULSE_WIDTH 1500		// Middle = 1.5 ms
#define PWM_CHANNEL_MOTOR 0         // Use PWM channel 0
#define PB12_PIN 12					// PB12 corresponds to pin 12

void PWM_motor_init() {
	
	// Enable PIOB and PWM peripheral clocks
    PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
	PMC->PMC_PCER0 |= (1 << ID_PIOC);  // Enable clock for PIOC
    //PMC->PMC_PCER1 |= (1 << (ID_PWM - 32));  // Enable clock for PWM
	PMC->PMC_PCER1|=PMC_PCER1_PID36;

    // Configure PIOB pin 12 (PB12) for PWM output
    PIOB->PIO_PDR |= PIO_PDR_P12;    // Disable PIO control for PB12 (peripheral control)
    PIOB->PIO_ABSR |= PIO_ABSR_P12;  // Select peripheral B for PB12 (PWM functionality)
	
	// enable PIO and enable Output
	PIOC->PIO_PER |= PIO_PER_P23;
	PIOC->PIO_OER |= PIO_OER_P23;

	// Set the PWM clock (PWM_CLK is MCK divided by a prescaler)
	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); 
	/*PWM_CLK_PREA(0): Selects Clock A without any prescaling.
	PWM_CLK_DIVA(84): Divides the 84 MHz master clock by 84 to get 1 MHz for the PWM clock.
	
	This 1 MHz PWM clock means that each clock cycle represents 1 microsecond,
	making it easy to handle pulse widths for the servo,
	as you can directly set the pulse width in microseconds (e.g., 1500 for 1.5 ms).*/

	// Configure PWM channel
	PWM->PWM_SCM = PWM_SCM_UPDM_MODE0;
	
	PWM->PWM_CH_NUM[PWM_CHANNEL_MOTOR].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;  // Use Clock A with inverted polarity
	PWM->PWM_CH_NUM[PWM_CHANNEL_MOTOR].PWM_CPRD = PWM_PERIOD;        // Set period to 20 ms (20000 us)
	PWM->PWM_CH_NUM[PWM_CHANNEL_MOTOR].PWM_CDTY = MID_PULSE_WIDTH;   // Start with the mid-point pulse (1.5 ms)

	// Enable the PWM channel
	PWM->PWM_ENA = (1 << PWM_CHANNEL_MOTOR);

}

//takes a value between 0 and 20000 
void set_PWM_duty_motor(uint16_t pulse_width) { //change of uint16_t with float
	if (pulse_width < PWM_MIN) {
		pulse_width = PWM_MIN;  // Clamp to minimum
		}
		
	else if (pulse_width > PWM_MAX) {
		pulse_width = PWM_MAX;  // Clamp to maximum
		}
	

	// Set the new duty cycle (pulse width)
	PWM->PWM_CH_NUM[PWM_CHANNEL_MOTOR].PWM_CDTYUPD = pulse_width;
    PWM->PWM_SCUC = PWM_SCUC_UPDULOCK; //update at the new clock cycle
}

 
