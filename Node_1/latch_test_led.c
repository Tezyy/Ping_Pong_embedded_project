/*Some parts of this code come from the slides from the lab lecture 2*/

#define BASE_ADDRESS 0x1000 // External memory base address A CHANGER
#define LED_PORT 0x0500 // Example address for the latch output connected to LEDs A CHANGER

#include "sram.h" //???
#include "../misc/memory_mapping.h" //???
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

void xmem_init ( void )
{
    MCUCR |= (1 << SRE ); // enable XMEM  
    SFIOR |= (3 << XMM0); // Mask PC7-PC4 for JTAG
}


void xmem_write(uint8_t data, uint16_t addr)
{
    volatile char *ext_mem = (char *)BASE_ADDRESS;
    ext_mem[addr] = data;
}

int main(void) {
    uint8_t led_data = 0x01; // first LED on
    
    while (1) {
        xmem_write(led_data, LED_PORT); // Write LED pattern to the latch
        led_data = led_data << 1;       // Shift to the next LED
        if (led_data == 0)
        {
            led_data = 0x01;            // Reset pattern if all LEDs shifted out
        }
        _delay_ms(500); // Add a delay to make the blinking visible
    }
}
