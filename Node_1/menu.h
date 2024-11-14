#ifndef MENU_H
#define MENU_H
#include "joystick.h"
#include "oled.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <string.h>

#define NUM_OPTIONS 2

void fleche();
void print_menu();
void choix_menu(uint8_t current_selection);

#endif // MENU_H

