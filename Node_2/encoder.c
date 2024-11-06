#include <sam.h>

// Initialize TC2 in quadrature mode for channel 0
void init_TC2_quadrature_mode() {
	// Enable the clock for port C
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
		
	// Enable the clock for TC2
	PMC->PMC_PCER1 |= (1 << (ID_TC6-32));

	// Configure PC25 and PC26 as inputs
	PIOC->PIO_OER |= (PIO_OER_P25 | PIO_OER_P26);
	PIOC->PIO_PDR |= (PIO_OER_P25 | PIO_OER_P26);
	PIOC-> PIO_ABSR |= (PIO_OER_P25 | PIO_OER_P26);
	//PIOC->PIO_PUER |= (PIO_PUER_P25 | PIO_PUER_P26); // Enable pull-up resistors for PC25 and PC26
	//PIOC->PIO_PUER &= ~(PIO_PUER_P25 | PIO_PUER_P26); //Disable pull up resistors


	// Configure the channel 0 for quadrature mode
	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0; //|          // Set clock source to XC0
// 	TC_CMR_LDRA_RISING |        // Capture on rising edge for signal A ??
// 	TC_CMR_LDRB_FALLING ;        // Capture on falling edge for signal B
	TC2->TC_BMR = TC_BMR_QDEN |                 // Enable quadrature decoder mode
	TC_BMR_POSEN |					// Enable position counter
	TC_BMR_MAXFILT(1) |
	TC_BMR_EDGPHA;            // TC_WPMR ?? à rajouter si ça marche pas       

	// Start the counter
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

// Function to read encoder position
uint8_t read_pin_PC25() {
	return (PIOC->PIO_PDSR & PIO_PDSR_P25) ? 1 : 0;
}

uint8_t read_pin_PC26() {
	return (PIOC->PIO_PDSR & PIO_PDSR_P26) ? 1 : 0;
}

uint16_t read_encoder_position() {
	uint16_t position = TC2->TC_CHANNEL[0].TC_CV;
	return position;
}

