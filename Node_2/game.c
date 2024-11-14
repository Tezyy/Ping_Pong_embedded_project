#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static int timer_now = 0;
static int last_time = 0;




//I assume value will between 0 and 2100 if the IR sensor has been covered or not
//starting_time of the game
Time score_counter (int value, int starting_time){
    static uint8_t score = 0;
    static ancient_tick = 0;
    
	static Time t = (Time){.hours = 0, .minutes = 0, .seconds = 0, .msecs = 0};
    //static uint64_t time_controller = 0;

    
    if ( value < 500){ //trouver valeur
	
		
		timer_now=time_now();
		if (!(totalSeconds((uint64_t)(timer_now-last_time)) < 5) ){
			printf("timer now :%d\r\n",(int)timer_now);
			t=time_split((uint64_t)(timer_now-starting_time));
			//printf("t: " time_fmtStr "\n", time_fmtParam(t));
			last_time=timer_now;
			return t;
	}
	
	}
    
}
void game_init(void){
	
	// Activer l'horloge pour le port B
	PMC->PMC_PCER1 |= (1 << ID_PIOA);
	//enable pin 53 as output
	REG_PIOA_PER = PIO_PER_P11;
	REG_PIOA_OER = PIO_PER_P11;
	//set as high as it is active low
	//PIOA-> PIO_SODR |= PIO_PA16;
	

}


void solenoid (uint8_t state){
	static state_before = 0;
	 if (state_before != state) {
		 if (state == 1) {
			 // Mettre pin 53 � un niveau bas poru trigger
			 REG_PIOA_SODR = PIO_SODR_P11;
			 printf("0000000000_____________00000000000000000000000000\r\n");
			 } 
			 else {
			 // Mettre PB27 � un niveau bas
			 REG_PIOA_CODR = PIO_CODR_P11;
			 printf("22222222222222222222222222222222222222222222\r\n");
			 
		 }
		 
		 // Mettre � jour l'�tat pr�c�dent
		 state_before = state;
	 }
 }
	
