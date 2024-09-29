#include "oled.h"


// Initialization of the Oled
// described in Oled DataSheet
void oled_init()
{
    oled_command_write(0xae); // display off 
    oled_command_write(0xa1); //segment remap 
    oled_command_write(0xda); //common pads hardware: alternative 
    oled_command_write(0x12); 
    oled_command_write(0xc8); //common output scan direction:com63~com0 
    oled_command_write(0xa8); //multiplex ration mode:63 
    oled_command_write(0x3f); 
    oled_command_write(0xd5); //display divide ratio/osc. freq. mode 
    oled_command_write(0x80); 
    oled_command_write(0x81); //contrast control 
    oled_command_write(0x50); 
    oled_command_write(0xd9); //set pre-charge period 
    oled_command_write(0x21); 
    oled_command_write(0x20); //Set Memory Addressing Mode 
    oled_command_write(0x02); 
    oled_command_write(0xdb); //VCOM deselect level mode 
    oled_command_write(0x30); 
    oled_command_write(0xad); //master configuration 
    oled_command_write(0x00); 
    oled_command_write(0xa4); //out follows RAM content 
    oled_command_write(0xa6); //set normal display 
    oled_command_write(0xaf); // display on

    oled_clear(); // clear the screen 
    // May set the cursor in (0;0) ??
}

// Send command to the Oled
//Same way like for the ram
void oled_command_write(uint8_t command){
    volatile char* cmd_prt = (char*)OLED_COMMAND_ADDRESS;
    cmd_prt[0]=command ; 
}

// Send data to the Oled
void oled_data_write(uint8_t data){
    volatile char* data_prt = (char*)OLED_DATA_ADDRESS;
    data_prt[0]=command ;
}

// reset oled screen and re_initializes it
void oled_reset(){
    
}

// set to (o;o)
void oled_home(){
    NULL;
}

// set selected line
void oled_line(uint8_t line){
    NULL;
}

// set slected column
void oled_column(uint8_t column){
    NULL;
}

// clear the specified line
// by writing 0 to all 128 columns
void oled_clear_line(uint8_t line){
    for (uint8_t i =0;i<128;i++){
        oled_data_write(0b00);  //A FINIR
    }
}

// clear all the screen
void oled_clear(){
    NULL;
}

// Set selected position
// Move the cursor to the specified 
// columns and lines
void oled_set_pos(uint8_t row, uint8_t column){
    oled_command_write((0xB0 + row)); //
    uint8_t lower = col & 0b1111;
    uint8_t higher = (col & 0b11110000) >> 4;
    higher |= 0b10000;
    oled_command_write(lower);
    oled_command_write(higher);
}

// send character
void oled_print_char (char *data){
    NULL;
}
