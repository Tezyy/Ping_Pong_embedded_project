#ifndef PI_H_
#define PI_H_

#define Kp 1
#define Ki 0.8
#define T 0.001
#define ENCODER_MAX 5300
#define ENCODER_MIN 0

int16_t PI(uint16_t target_position, int16_t current_position);

#endif /* PI_H_ */
