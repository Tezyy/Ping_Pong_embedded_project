#include <sam.h>

// Function to configure the PWM
void configure_pwm_channel1(void) {
    // Enable PIOB and PWM peripheral clocks
    PMC->PMC_PCER0 |= (1 << ID_PIOB);  // Enable clock for PIOB
    PMC->PMC_PCER1 |= (1 << (ID_PWM - 32));  // Enable clock for PWM

    // Configure PIOB pin 13 (PB13) for PWM output
    PIOB->PIO_PDR |= PIO_PDR_P13;    // Disable PIO control for PB13 (peripheral control)
    PIOB->PIO_ABSR |= PIO_ABSR_P13;  // Select peripheral B for PB13 (PWM functionality)

    // Configure the PWM channel
    PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024;  // Set clock to master clock/1024
    PWM->PWM_CH_NUM[1].PWM_CPRD = 8192;  // Set period to 20ms (assuming a 84MHz clock)
    PWM->PWM_CH_NUM[1].PWM_CDTY = 409;  // Set duty cycle to 0.9ms (initial position)

    // Enable the PWM channel
    PWM->PWM_ENA = PWM_ENA_CHID1;  // Enable PWM channel 1
}
