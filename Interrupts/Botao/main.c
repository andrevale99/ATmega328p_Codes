/**
 * @author Andre Menezes de Freitas Vale
 * 
 * @brief Codigo que utiliza da interrupcao externas PCINTXX
 * para criar uma logica de semaforo simples 
 * 
*/

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>

#define VRD PB0
#define AMA PB1
#define VER PB2

#define BT PB3

#define SetBit(port, pin) (port |= (1<<pin))
#define ClrBit(port, pin) (port &= ~(1<<pin))
#define ToggleBit(port, pin) (port ^= (1<<pin))
#define TestBit(port, pin) (port &= (1<<pin))

//===================================================
//  VARIAVEIS
//===================================================
volatile uint8_t i = 0;

//===================================================
//  PROTOTIPOS
//===================================================
void setup();

void gpio_setup();
void interrupts_setup();

void logica_semaforo();

ISR(PCINT0_vect);
//===================================================
//  MAIN
//===================================================
int main()
{
    setup();
    sei();

    for(;;)
    {
        SetBit(PORTB, VRD);
    }

    return 0;
}

//===================================================
//  FUNCOES
//===================================================
void setup()
{
    gpio_setup();

    interrupts_setup();
}

void gpio_setup()
{  
    SetBit(DDRB, VRD);
    SetBit(DDRB, AMA);
    SetBit(DDRB, VER);

    ClrBit(DDRB, BT);

    SetBit(PORTB, BT);
}

void interrupts_setup()
{
    SetBit(PCICR, PCIE0);

    SetBit(PCMSK0, PCINT3);
    SetBit(PCMSK0, PCINT4);
}

void logica_semaforo()
{
    for(i=0; i<5; ++i)
    {
        ToggleBit(PORTB, VRD);
        _delay_ms(200);
    }

    ToggleBit(PORTB, AMA);
    _delay_ms(2000);
    ToggleBit(PORTB, AMA);

    SetBit(PORTB, VER);
    _delay_ms(2500);
    for(i=0; i<5; ++i)
    {
        ToggleBit(PORTB, VER);
        _delay_ms(500);
    }
    ClrBit(PORTB, VER);
}

ISR(PCINT0_vect)
{
    if(!(PINB & (1<<BT)))
        logica_semaforo();
        
    /*if(!(PINB & (1<<BT_2)))
        ClrBit(PORTB, VRD);*/
}
