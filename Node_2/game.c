#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"


//I assume value will between 0 and 100 if the IR sensor has been covered or not
uint8_t goal_counter (int value){
    static uint8_t score = 0;
    static uint64_t timer_now = 0;
    static uint64_t last_time = 0;
    static uint64_t time_controller = 0;

    timer_now=time_now();
    if ( value < VALEUR){ //trouver valeur
        if (timer_now - last_time > 5000){//1 tick = 1ms ?
            score++;
            last_time=time_now();
        }
        
    }
    return score;
}