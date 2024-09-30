#ifndef OLED_H
#define OLED_H

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS    0x1200

#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>

// Initialization of the Oled
void oled_init();

// Send command to the Oled
void oled_command_write(uint8_t command);

// Send data to the Oled
void oled_data_write(uint8_t data);

// reset oled screen and re_initializes it
void oled_reset();

// set to (o;o)
void oled_home();

// set selected line
void oled_line(uint8_t line);

// set selected column
void oled_go_to_column(uint8_t column);

// clear the specified line
// by writing 0 to all 128 columns
void oled_clear_line(uint8_t line);

// clear all the screen
void oled_clear();

// Set selected position
// Move the cursor to the specified
// columns and lines
void oled_set_pos(uint8_t row, uint8_t column);

// send character
void oled_print_char (char c);

void oled_print_string(char* strg);

#endif
