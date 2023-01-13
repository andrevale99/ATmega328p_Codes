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
#include <stdbool.h>

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
    }

    return 0;
}
//===================================================
//  FUNCOES
//===================================================
/**
 * @brief Funcao de setup
*/
void setup()
{

}