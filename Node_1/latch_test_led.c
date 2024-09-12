/*Some parts of this code come from the slides from the lab lecture 2*/
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 4915200
#include <util/delay.h>

#include  <stdint.h>
#include <stdlib.h>

void xmem_init ( void )
{
    MCUCR |= (1 << SRE ); // enable XMEM  
    SFIOR |= (1 << XMM0); // Mask PC7-PC4 for JTAG
}


void xmem_write(uint8_t data, uint16_t addr)
{
    volatile char *ext_mem = (char *)BASE_ADDRESS;
    ext_mem[addr] = data;
}

int main() {
    DDRE = 0b10; //Sets ALE (pin 1 on port E) as output.
    PORTE = 0b10; //Sets ALE high. Tells the latch that there will now be an address to be saved.
    PORTA = 0b000001; //Sending an adress.

    _delay_ms(2000);

    PORTE = 0b00; //Sets ALE low. Now the address value is stored.

    _delay_ms(2000);

    PORTA = 0b01010101; //Sends out new address.

    _delay_ms(2000);

    PORTE = 0b10; //Old address is removed  and the new one is sent through.
}
