#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "i2c_lib.h"

//==============================================
// DEFINES
//==============================================
#define DS3231_ADDRESS 0xD0

//==============================================
// VARIAVEIS
//==============================================
volatile uint8_t addr = 0x00;
volatile bool opr_complete = false;
//==============================================
// PROTOTIPOS
//==============================================
void start_leitura();

ISR(TWI_vect);

//==============================================
// MAIN
//==============================================
int main(void)
{
    while (true)
    {
    }

    return 0;
}
//==============================================
// FUNCOES
//==============================================
void start_leitura()
{
    i2c_start_bit();
}

ISR(TWI_vect)
{
    switch (TWSR & TW_STATUS_MASK)
    {
    case TW_START:
        TWDR = DS3231_ADDRESS | TW_WRITE;
        TWCR &= ~(1 << TWSTA); // Desativa o start bit
        break;

    case TW_MT_SLA_ACK:
        TWDR = addr;
        break;

    case TW_MT_DATA_ACK:
        TWCR |= (1 << TWSTA); // Bit de restart
        break;

    case TW_REP_START:
        TWDR = DS3231_ADDRESS | TW_READ;
        TWCR &= ~(1 << TWSTA); // Desativa o start bit
        break;

    case TW_MR_SLA_ACK:
        TWCR &= ~(1 << TWEA);
        break;

    case TW_MR_DATA_NACK:
        i2c_stop_bit();
        data = TWDR;
        opr_complete = true;
        break;

    default:
        break;
    }
}