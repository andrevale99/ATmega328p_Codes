#ifndef _74HC595_H
#define _74HC595_H

#include <avr/io.h>

#include <stdint.h>

#define SH_CP PD0
#define ST_CP PD1
#define DS PD2

void begin_74hc595();

#endif
