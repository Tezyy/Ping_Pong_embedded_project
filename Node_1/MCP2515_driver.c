#include "MCP2515.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include "spi.h"
uint8_t read(uint8_t adress){
    clear_bit(PORTB, PB4);

    spi_receive(MCP_READ);
    spi_receive(address);
    char result = spi_receive();

    set_bit(PORTB, PB4);

    return result;

};

void write(uint8_t adress, uint8_t data ){
    clear_bit(PORTB, PB4);

    spi_receive(MCP_WRITE);
    spi_receive(address);
    spi_receive(data);

    set_bit(PORTB, PB4);

    return result;
};

void req_to_send(uint8_t stat){
    clear_bit(PORTB, PB4);
    spi_receive(stat);
    set_bit(PORTB, PB4);
};

uint8_t mcp2515_read_status(){
    clear_bit(PORTB, PB4);
    uint8_t result = spi_receive(MCP_READ_STATUS);
    set_bit(PORTB, PB4);
};

void mcp2515_modify_bit(uint8_t address, uint8_t mask, uint8_t data){
    clear_bit(PORTB, PB4);
    spi_receive(MCP_BITMOD);
    spi_receive(address);
    spi_receive(mask);
    spi_receive(data);
    set_bit(PORTB, PB4);
};

void mcp2515_reset(){
    clear_bit(PORTB, PB4);
    spi_receive(MCP_RESET);
    set_bit(PORTB, PB4);
};

uint8_t mcp2515_init(){
    init_spi();
    mcp2515_reset();
}; 