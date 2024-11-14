#include <sam.h>
#include "encoder.h"

// Initialize TC2 in quadrature mode
void init_TC2_quadrature_mode() {

	PMC->PMC_PCER0 |= (1 << ID_PIOC); // Enable the clock for port C
	PMC->PMC_PCER1 |= (1 << (ID_TC6-32)); // Enable the clock for TC2

	// Configure PC25 and PC26 as inputs
	PIOC->PIO_OER |= (PIO_OER_P25 | PIO_OER_P26);
	PIOC->PIO_PDR |= (PIO_OER_P25 | PIO_OER_P26);
	PIOC-> PIO_ABSR |= (PIO_OER_P25 | PIO_OER_P26);

	// Configure the channel 0 for quadrature mode
	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0;          // Set clock source to XC0
	TC2->TC_BMR = TC_BMR_QDEN |								// Enable quadrature decoder mode
	TC_BMR_POSEN |											// Enable position counter
	TC_BMR_MAXFILT(1) |										// Filter
	TC_BMR_EDGPHA;											// Tip : add TC_WPMR register if it does not work       

	// Start the counter
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

// Function to read pins
uint8_t read_pin_PC25() {
	return (PIOC->PIO_PDSR & PIO_PDSR_P25) ? 1 : 0;
}

uint8_t read_pin_PC26() {
	return (PIOC->PIO_PDSR & PIO_PDSR_P26) ? 1 : 0;
}

//Function to read encoder position
uint16_t read_encoder_position() {
	uint16_t position = TC2->TC_CHANNEL[0].TC_CV;
	return position;
}

