#ifndef GAME_H
#define GAME_H

#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"

Time score_counter (int value, int starting_time);
void game_init (void);
void solenoid (uint8_t state);

#endif
