/**
 * @brief Biblioteca baseada nos códigos de 
*/

#ifndef I2C_LIB_H
#define I2C_LIB_H

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/twi.h> 
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>

#define I2C_DDR DDRC
#define I2C_PORT PORTC

#define SCL PC5
#define SDA PC4

void i2c_init();
void i2c_init_pullup();
void i2c_unit();

void i2c_start_bit();
void i2c_stop_bit();

#endif
