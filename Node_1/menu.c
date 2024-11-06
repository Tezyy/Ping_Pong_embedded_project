#include "menu.h"
#include "joystick.h"
#include <string.h>


void fleche(){
	oled_print_char('<');oled_print_char('-');
}

const char* menu_options[NUM_OPTIONS] = {
	"Start Game",
	"Option 2"
};

void print_menu() {
	oled_clear();
	for (uint8_t i=0; i<NUM_OPTIONS; i++){
		oled_set_pos(i,0);
		oled_print_string(menu_options[i]);
	}
}

void choix_menu(uint8_t current_selection){
	for (uint8_t i=0; i<NUM_OPTIONS; i++){
		if (i== current_selection){
			oled_set_pos(i,110);
			fleche();
		}
		else {
			oled_set_pos(i,110);
			oled_print_string("  ");
		}
	}
}
