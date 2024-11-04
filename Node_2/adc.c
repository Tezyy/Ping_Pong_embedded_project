#include "adc.h"
#include <sam.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


void adc_init(void){

	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); 	//set the clock : ID ADC = 37 mais registre séparé en 2 
											//donc -32 pour arriver au bon endroit, 
											//2 regsitres PMC là on est dans le 1, et on veut 5	
	ADC->ADC_MR = ADC_MR_FREERUN; 	//Set ADC to free run mode

	ADC->ADC_CHER = ADC_CHER_CH0; 	//Set AD0 en output
	

	
	ADC->ADC_CR = ADC_CR_START; 	//Start ADC conversion
	
}



uint16_t adc_read(){
	uint16_t ir_level = ADC->ADC_CDR[0];
	return(ir_level);
}
