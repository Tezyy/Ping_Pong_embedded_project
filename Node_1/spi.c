#include spi.h

void init_spi(){
  DDRB |= (1<<PB5) | (1<<PB7) | (1<<PB4); //MOSI(PB5) SCK(PB7) SS(PB4) output
  DDRB &= ~(1 << PB6); // MISO (PB6) input
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // enable SPI, set SPI mode 0, set SCK rate to F_CPU/ 16 
  PORTB |= (1 << PB4); // Set SS high (deselect slave)
}

void spi_transmit(uint8_t data){
  SPDR=data;
  while(!(SPSR & (1<<SPIF)));
}

void spi_receive(){
  SPDR = 0xFF;
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}
// est ce qu'on a vraiment besoin des fonctions qui suivent ? Ca suffirait pas juste de mettre le slave dans l'init et basta ? Jpense que ce serait plus simple mais idk, j'attends vos avis
void SPI_select_slave(void) {
    PORTB &= ~(1 << PB4); // Pull SS low to select the slave
}

void SPI_deselect_slave(void) {
    PORTB |= (1 << PB4); // Set SS high to deselect the slave
}



