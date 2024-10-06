#include spi.h

void init_spi(){
  DDRB |= (1<<PB5) | (1<<PB7) | (1<<PB4); //MOSI(PB5) SCK(PB7) SS(PB4) output
  DDRB &= ~(1 << PB6); // MISO (PB6) input
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // enable SPI, set SPI mode 0, set SCK rate to F_CPU/ 16 
  PORTB |= (1 << PB4); // active SS
}


