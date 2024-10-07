#define F_CPU 4915200UL
#include <util/delay.h>

#define BASE_ADDRESS_OLED 0x1000
#define BASE_ADDRESS_ADC 0x1400
#define BASE_ADDRESS_SRAM 0x1800

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"


void exercise1 (void){
	unsigned char mess = USART_Receive();
	_delay_ms(1000);
	USART_Transmit(mess);
	printf("ouioui");
	_delay_ms(1000);
}

void exercise2 (void){
	//Pour faire ce test we have to comment XMEM_init parce que en gros dans XMEM _init SRE overide toutes les directions de pin
	//donc set les DDR manuellement c'est contradictoire avec set SRE, et le reste du temps SRE gère si les pins seront en entrée
	//ou en sortie automatiquement
	
	//SRAM start:         0x1800    1100 000000000
	//SRAM end:           0x1FFF    1111 111111111
	//ADC start:          0x1400    1010 000000000
	//ADC end:            0x17FF    1011 111111111
	//OLED-data start:    0x1200    1001 000000000
	//OLED-data end:      0x13FF    1001 111111111
	//OLED-command start: 0x1000    1000 000000000
	//OLED-command end:   0x11FF    1000 111111111
	
	DDRE = 0b10;
	DDRA = 0xFF;
	DDRC = 0b1111;
	
	//PORTA = 0b00000010; //Sending an adress.
	PORTC = 0b00001000; //Sending an SRAM adress
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	
	_delay_ms(1000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(1000);
	
	//PORTA = 0b00000010; //Sending an adress.
	PORTC = 0b00000010; //Sending an OLED adress
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	
	_delay_ms(1000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(1000);
	
	//PORTA = 0b00000010; //Sending an adress.
	PORTC = 0b00000100; //Sending an ADC adress
	PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
	
	_delay_ms(1000);
	PORTE = 0b00; //Sets ALE low. Now the address value is stored.
	_delay_ms(1000);
}

void exercise3(){
	//copier coller ça dans la main pour avoir des résultats !!!!
	/*adc_data_t adc_inputs=adc_read();
	uint8_t adc_x_value = adc_inputs.joystick_x;
	uint8_t adc_y_value = adc_inputs.joystick_y;
	uint8_t adc_left_slider = adc_inputs.slider_left;
	uint8_t adc_right_slider = adc_inputs.slider_right;

	JoystickPosition pos = getJoystickPosition(adc_x_value, adc_y_value, calib);
	JoystickDirection dir = getJoystickDirection(pos);
	SliderPosition slider_pos = getSliderPosition(adc_left_slider, adc_right_slider);
	
	printf("Joystick X: %d%%, Y: %d%%\n", pos.x_percent, pos.y_percent);
	printf("Slider Left: %d%%, Slider Right: %d%%\n", slider_pos.left_percent, slider_pos.right_percent);
	
	switch(dir) {
		case LEFT:   printf("Direction: LEFT\n");   break;
		case RIGHT:  printf("Direction: RIGHT\n");  break;
		case UP:     printf("Direction: UP\n");     break;
		case DOWN:   printf("Direction: DOWN\n");   break;
		default:     printf("Direction: NEUTRAL\n"); break;*/
}

void exercise4_test(){
	oled_set_pos(1,110);
	fleche();
	_delay_ms(1000);
	//if blablabla entre les 2 pour selection du menu
	oled_clear();
	oled_set_pos(3,110);
	fleche();
	_delay_ms(500);
	//oled_print_char('h');
	//oled_print_string("bonjour");
}

void exercise4_menu(){
	/*	
	if (direction == UP && current_selection > 0) {
	current_selection--;
	print_menu();
	choix_menu(current_selection);
	}
	else if (direction == DOWN && current_selection < NUM_OPTIONS-1) {
	current_selection++;
	print_menu();
	choix_menu(current_selection);
	}
	
	if (state.button_left) {
		oled_clear();
		oled_set_pos(0,0);
		switch(current_selection){
			case 0 : oled_print_string("Choix : 1"); break;
			case 1 : oled_print_string("Choix : 2"); break;
			case 2 : oled_print_string("Choix : 3"); break;
			case 3 : oled_print_string("Choix : 4"); break;
		}
	}*/
}

int main(void)
{
	USART_Init(MYUBRR);
	init_printf();
	XMEM_init();
	//SRAM_test();
	adc_init();
	JoystickCalibration calib = calibrateJoystick();
	oled_init();
	init_spi();	
	
	print_menu();
	uint8_t current_selection=0;
	DDRB = 0b11; //left and right button on the atmega	//voir si on veut garder ça comme ça ou l'intégrer plus proprement dans le .c correspondant
	

	while(1)
	{
		//laisser ça constamment
		JoystickPosition pos;
		JoystickDirection direction;
		
		adc_data_t adc_inputs = adc_read();
		pos = getJoystickPosition(adc_inputs.joystick_x, adc_inputs.joystick_y, calib);
		direction = getJoystickDirection(pos);
		Buttons state = buttons_read();
		
		// maintenant c'est bon on peut faire nos tests et modifs
		spi_select_slave();
		spi_transmit(0xAA);
		uint8_t received_data=spi_receive();
		spi_deselect_slave();
		
		printf("data received by the spi : 0x%02X\n", received_data);
		
		_delay_ms(200);
		
		}
		
	return(0);
}
