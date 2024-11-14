#ifndef ENCODEUR_H
#define ENCODEUR_H

#include <sam.h>

void init_TC2_quadrature_mode(void);
uint8_t read_pin_PC25();
uint8_t read_pin_PC26();
uint16_t read_encoder_position(void);

#endif // ENCODEUR_H
