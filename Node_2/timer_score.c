#include <sam.h>
#include "can.h"
#include "time.h"
#include "uart.h"
#include "timer_score.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*
Systick : temporisateur matériel présent dans les microcontrôleurs ARM Cortex-M conçu pour mesurer le temps;
il compte des cycles d'horloge et génère des interruptions régulières, permettant le suivi du temps ou la génération de délais.

time_init() : calcule et configure "calib" pour correspondre aux cycles d'horloge nécessaires pour 1 milliseconde
(calibrage est basé sur la valeur d’horloge définie par SysTick)

time_now() : provides the current time in terms of ticks (or clock cycles) since the timer was initialized

	"now" : stores the accumulated time in ticks, updated every time the SysTick timer overflows and triggers an interrupt (handled by SysTick_Handler);
	it keeps track of elapsed time across multiple timer overflows.

	"calib - SysTick->VAL" :
	- "SysTick->VAL" holds the current countdown value of the SysTick timer, counting down from SysTick->LOAD to 0.
	- "calib" is the calibrated number of ticks for a specific interval (e.g., 1 ms), which was set in SysTick->LOAD.
	- "calib - SysTick->VAL" computes how many ticks have passed since the last overflow.
	
	"now + (calib - SysTick->VAL)" : gives the current time by adding the accumulated ticks (now) and the current partial interval (calib - SysTick->VAL)
*/

static uint64_t start_time = 0;
static uint64_t end_time = 0;
static uint64_t en_cours = 0;

void start_score_timer(void) {
	start_time = time_now();
	en_cours = 1;
}

uint64_t stop_score_timer(void) {
	end_time = time_now();
	en_cours = 0;

	return end_time - start_time;  //return le temps écoulé
}

void reset_score_timer(void) {
	start_time = 0;
	end_time = 0;
	en_cours = 0;
}
