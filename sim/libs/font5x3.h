#ifndef FONT5x3_H
#define FONT5x3_H

#ifdef __AVR__
#include <avr/pgmspace.h>
#else
typedef const unsigned char prog_uint8_t;
#endif

extern prog_uint8_t font5x3[][3];

#endif //FONT_H
