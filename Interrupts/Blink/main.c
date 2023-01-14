/**
 * @author Andre Menezes de Freitas Vale
 * 
 * @brief Codigo que utiliza da interrupcao externas PCINTXX
 * para criar uma logica de semaforo simples 
 * 
 * @note O PWM é gerado pelo pino PB1 (OC1A) sem o auxilio de interrupcao,
 * pois a configuracao do TIMER 1 permite isso, ou seja, a mudanca ocorrera
 * de forma assincrona.
 * 
*/

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>

#define SetBit(port, pin) (port |= (1<<pin))
#define ClrBit(port, pin) (port &= ~(1<<pin))
#define ToggleBit(port, pin) (port ^= (1<<pin))
#define TestBit(port, pin) (port & (1<<pin))

//===================================================
//  VARIAVEIS
//===================================================

//===================================================
//  PROTOTIPOS
//===================================================
void setup();

ISR(TIMER1_COMPA_vect);
//===================================================
//  MAIN
//===================================================
int main()
{
    setup();
    sei(); //Ativa as interrupcoes globais

    for(;;)
    {

    }

    cli(); //Desativa as interrupcoes globais

    return 0;
}
//===================================================
//  FUNCOES
//===================================================
/**
 * @brief Configuracao do timer 1 e do pino PB5
 * 
 * @note O modo utlizado eh o 4 (CTC) o qual ira
 * gerar uma interrupcao quando o valor do contador
 * chegar no valor colocado no registrador OCR1A.
 * O prescale do contade é de 1024 (16e6/1025 = 15625Hz)
*/
void setup()
{
    SetBit(DDRB, DDB5);
    ClrBit(PORTB, PB5);

    SetBit(TCCR1B, WGM12);
    SetBit(TCCR1B, CS12);
    SetBit(TCCR1B, CS10);

    SetBit(TIMSK1, OCIE1A);

    OCR1A = 15625;
}

/**
 * @brief Funcao de interrupcao de comapraco quando 
 * o contador chegar no valor de OCR1A
*/
ISR(TIMER1_COMPA_vect)
{
    ToggleBit(PORTB, PB5);
}