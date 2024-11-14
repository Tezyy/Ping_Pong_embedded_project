#ifndef GAME_H
#define GAME_H

#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"

//I assume value will between 0 and 100 if the IR sensor has been covered or not
Time score_counter (int value, int starting_time);
void game_init (void);
void solenoid (uint8_t state);


#endif
