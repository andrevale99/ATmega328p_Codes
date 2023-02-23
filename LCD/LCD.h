#ifndef LCD_H
#define LCD_h

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>

#include "Utilitarios.c"

#define DADOS_LCD PORTD
#define CONTR_LCD PORTB
#define E PB1
#define RS PB0

/*0 para via de dados do LCD nos 4 LSBs do PORT
empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7), 1 para via de
dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5,
Px6-D6, Px7-D7) */
#define nibble_dados 1

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define PULAR_LINHA 0xA0

#define pulso_enable() _delay_us(1); SetBit(CONTR_LCD,E); _delay_us(1); ClrBit(CONTR_LCD,E); _delay_us(45)

void inic_LCD_4bits();
void cmd_LCD(unsigned char c, char cd);
void escreve_LCD(char *c);

#endif