#include "motor.h"
#include "can.h"
#include "time.h"
#include <sam.h>

#define PWM_PERIOD 20000      // PWM period in microseconds (20 ms)
#define PWM_MAX 19000
#define PWM_MIN 0

#define PWM_CHANNEL_MOTOR 0         // Use PWM channel 0
#define PB12_PIN 12           // PB12 corresponds to pin 12

//set_PWM_duty_motor(PWM_value_motor((receive_can.byte[1]-128)));

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

//takes a value between 900 and 2100 (actually 0 and 20000 but will use a value in this range)
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

uint16_t PWM_value_motor(int8_t input_joystick){ //input_joystick = receive_can.byte[1]-128 [-128, 128]
	uint16_t result = 0;
	
	
	if (input_joystick < -15){
		if (input_joystick < -110) input_joystick =-110;
		input_joystick = -input_joystick;
		//PIOC->PIO_SODR = PIO_PC23;  // Forward direction (PHASE = 1)
		result = (uint16_t)(181.8*input_joystick);
	}
		
	if (input_joystick>15) {
		if (input_joystick > 110) input_joystick = 110;
		//PIOC->PIO_CODR = PIO_PC23;  // Reverse direction (PHASE = 0)
		result = (uint16_t)(181.8*input_joystick);
	}
	else {
	result=0;
	}
	
	printf("result = %d\n\r", result);
	return result;
}
 
uint16_t wanted_encoder_position(int8_t joystick_x){
	uint16_t wanted_position = 0;
	if (joystick_x < 20){
		wanted_position = 0;
	}
	if (joystick_x > 20 && joystick_x < 40){
		wanted_position = 509;
	}
	if (joystick_x > 40 && joystick_x < 60){
		wanted_position = 1018;
	}
	if (joystick_x > 60 && joystick_x < 80){
		wanted_position = 1527;
	}
	if (joystick_x > 80 && joystick_x < 100){
		wanted_position = 2036;
	}
	if (joystick_x > 100 && joystick_x < 120){
		wanted_position = 2545;
	}
	if (joystick_x > 120 && joystick_x < 140){
		wanted_position = 3054;
	}
	if (joystick_x > 140 && joystick_x < 160){
		wanted_position = 3563;
	}
	if (joystick_x > 160 && joystick_x < 180){
		wanted_position = 4072;
	}
	if (joystick_x > 180 && joystick_x < 200){
		wanted_position = 4581;
	}
	if (joystick_x > 200 && joystick_x < 220){
		wanted_position = 5090;
	}
	if (joystick_x > 220){
		wanted_position = 5600;
	}
	return wanted_position;
}

void set_motor_forward() {
	PIOC->PIO_SODR = PIO_PC23;  // Forward direction
}

void set_motor_reverse() {
	PIOC->PIO_CODR = PIO_PC23;  // Reverse direction
}

void stop_motor() {
	set_PWM_duty_motor(0); // Set speed to 0
}

void control_motor_to_position(uint16_t current_position, uint16_t wanted_position) {
	int16_t error = wanted_position - current_position;
	int16_t integral = 0;
	
	const float KP = 0.5;     // Proportional gain
	const float KI = 0.05;    // Integral gain

	// Proportional term
	int16_t proportional = KP * error;

	// Integral term (accumulating error over time)
	integral += error;
	int16_t integral_term = KI * integral;

	// Control signal for motor speed
	int16_t control_signal = proportional + integral_term;

	// Determine motor direction based on control signal sign
	if (control_signal > 0) {
		set_motor_forward();
		set_PWM_duty_motor(control_signal); // valeurs de control_signal pas adaptées ??
		} else if (control_signal < 0) {
		set_motor_reverse();
		set_PWM_duty_motor(-control_signal); 
		} else {
		stop_motor(); // If control signal is zero, stop the motor
	}
}

void set_motor_position(uint16_t current_position, uint16_t wanted_position){
	if (wanted_position > current_position){
		while (wanted_position != current_position){
			PIOC->PIO_SODR = PIO_PC23; // Forward direction (PHASE = 1)
			set_PWM_duty_motor(10000); // fixe pour le moment
		}
	}
	else{
		while (wanted_position != current_position){
			PIOC->PIO_CODR = PIO_PC23;  // Reverse direction (PHASE = 0)
			set_PWM_duty_motor(10000);
		}
	}
	
}

 void set_motor_left(){
	 uint64_t duration = seconds(2);
	 uint64_t time = time_now();
	 while (time_now - time < duration){
		 set_motor_reverse();
	 }	 
 }
