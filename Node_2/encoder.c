#include <sam.h>

// Initialize TC2 in quadrature mode for channel 0
void init_TC2_quadrature_mode() {
	// Enable the clock for port C
	PMC->PMC_PCER1 |= (1 << ID_PIOC); // Activer l'horloge pour le port C

	// Configure PC25 and PC26 as inputs
	PIOC->PIO_OER &= ~(PIO_OER_P25 | PIO_OER_P26); // Clear output enable bits (set as input)
	PIOC->PIO_PUER |= (PIO_PUER_P25 | PIO_PUER_P26); // Enable pull-up resistors for PC25 and PC26
	
	// Enable the clock for TC2
	PMC->PMC_PCER0 |= (1 << ID_TC2);

	// Configure the channel 0 for quadrature mode
	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0 |          // Set clock source to XC0
	TC_CMR_LDRA_RISING |        // Capture on rising edge for signal A
	TC_CMR_LDRB_FALLING ;        // Capture on falling edge for signal B
	TC2->TC_BMR = TC_BMR_QDEN |                 // Enable quadrature decoder mode
	TC_BMR_POSEN |					// Enable position counter
	TC_BMR_MAXFILT(1);              // filter for noise               

	// Start the counter
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

// Function to read encoder position
int read_encoder_position() {
	return TC2->TC_CHANNEL[0].TC_CV; // Read position counter value
}
