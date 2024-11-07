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