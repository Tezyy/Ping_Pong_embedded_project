#include "adc.h"
#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


void adc_init(void){

	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	ADC->ADC_CR=ADC_CR_START;
	ADC->ADC_CHER = ADC_CHER_CH1; 	//Set AD0 en output
	ADC->ADC_MR = ADC_MR_FREERUN; 	//Set ADC to free run mode
}

uint32_t adc_read(){
	
	uint32_t ir_level = ADC->ADC_CDR[1];
	return(ir_level);
}

