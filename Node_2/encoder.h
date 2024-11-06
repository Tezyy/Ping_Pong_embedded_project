#ifndef ENCODEUR_H
#define ENCODEUR_H

#include <sam.h> // Include SAM-specific header for register definitions

// Initialize TC2 in quadrature mode to decode encoder signals
void init_TC2_quadrature_mode(void);

// Read the current encoder position from TC2
uint8_t read_pin_PC25();
uint8_t read_pin_PC26();
uint16_t read_encoder_position(void);

#endif // ENCODEUR_H
