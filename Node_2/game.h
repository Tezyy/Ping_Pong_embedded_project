#ifndef GAME_H
#define GAME_H

#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"

//I assume value will between 0 and 100 if the IR sensor has been covered or not
uint8_t goal_counter (int value);


#endif