#ifndef SRAM_H
#define SRAM_H

void XMEM_init(void); //Function to initialize external memory interface (XMEM)
void XMEM_write(uint8_t data, uint16_t addr); //Function to write data to external memory
void SRAM_test(void); //Function to test the SRAM memory

#endif /* SRAM_H */
