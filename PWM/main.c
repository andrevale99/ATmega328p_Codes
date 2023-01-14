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

//===================================================
//  MAIN
//===================================================
int main()
{
    setup();

    for(;;)
    {
        ToggleBit(PORTB, PB5);
        _delay_ms(100);
    }

    return 0;
}
//===================================================
//  FUNCOES
//===================================================
/**
 * @brief Funcao de setup
 * 
 * @note Ativa a porta PB1 como saida. Configura o Timer 1 
 * em modo 11 (PWM, fase correta) com a troca de pino OC1A
 * (PB1) ao atingir o TOP e o prescale de 16e6/256
*/
void setup()
{
    SetBit(DDRB, DDB1);
    ClrBit(PORTB, PB1);

    //  Pino para mostrar a mudanca assincrona 
    //do pino PB1
    SetBit(DDRB, DDB5);
    ClrBit(PORTB, PB5);

    SetBit(TCCR1A, COM1A0);
    SetBit(TCCR1A, WGM10);

    SetBit(TCCR1B, WGM13);
    SetBit(TCCR1B, CS12);

    //  A frequencia aqui é de 2Hz, basta realizar o calculo
    //do datasheet F_ocnxPFCPWM = F_clk_I/O / (2 * N * TOP)
    //onde o N e o prescale e TOP definido pelo OCR1A
    OCR1A = 62500/4;
}