#include "i2c_lib.h"

void i2c_init()
{
    I2C_DDR  &= ~((1<<SCL) | (1<<SDA));
    //Ajuste da frequência de trabalho - SCL = F_CPU/(16+2.TWBR.Prescaler)
    TWBR = 18;
    TWSR |= 0x01;//prescaler = 4;
    TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWIE); //habilita o TWI com interrupcao
}

void i2c_init_pullup()
{
    I2C_DDR  &= ~((1<<SCL) | (1<<SDA));
    I2C_PORT |= (1<<SCL) | (1<<SDA);

    i2c_init(); 
}

void i2c_unit()
{
    TWCR &= ~(1<<TWEN);
}

void i2c_start_bit()
{
    TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
}

void i2c_stop_bit()
{
    TWCR |= ((1<<TWINT) | (1<<TWSTO) | (1<<TWEN)) & ~(1<<TWSTA);
}

