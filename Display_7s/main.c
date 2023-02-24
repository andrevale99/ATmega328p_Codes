#ifndef F_CPU
    #define F_CPU 16000000Ul
#endif

#include <avr/io.h>
#include <util/delay.h>

#define BITS_7S PORTD

#define E_D1 PD7
#define E_D2 PB0

//==================================
//  MAIN
//==================================


//==================================
//  PROTOTIPOS
//==================================
void setup();

//==================================
//  MAIN
//==================================
int main(void)
{
    setup();

    while(1)
    {
        PORTB |= (1<<E_D2);
        _delay_ms(1000);
        PORTB &= ~(1<<E_D2);
        _delay_ms(1000);
    }

    return 0;
}

//==================================
//  FUNCOES
//==================================
void setup()
{
    //Desativa o RX e TX para serem usados
    //como pinos normais
    UCSR0B = 0x00;

    DDRD |= 0xFF; //Coloca os pinos como OUTPUTS
    DDRB |= 0x01;
    
    //Como é display de 7 segmentos com anodo comum
    //os led devem ser aterrados para ligar os leds
    PORTD &= ~((1<<PD0) | (1<<PD1)); 
    BITS_7S |= 0x00;
}