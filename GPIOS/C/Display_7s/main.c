/*
  ANODO COMUM: PINOS ACINADOS EM 0 E DISPLAY com
  5V EM COMUM

  CATODO COMUN: PINOS ACIONADOS EM 1 E DISPLAY COM
  GND EM COMUM

  O CÓDIGO ESTA PARA ANODO COMUM
  caso queira para catodo comum, so inverter
  os bits do driver
*/

#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define DIG_1 PB0
#define DIG_2 PB1

//Usei só para mapear
const struct 
{
  uint8_t d0 = ~0x3F;
  uint8_t d1 = ~0x06;
  uint8_t d2 = ~0x5B;
  uint8_t d3 = ~0x4F;
  uint8_t d4 = ~0x66;
  uint8_t d5 = ~0x6D;
  uint8_t d6 = ~0x7D;
  uint8_t d7 = ~0x07;
  uint8_t d8 = ~0x7F;
  uint8_t d9 = ~0x67;
}Driver;

//Melhor utilizar da forma de vetor
//codigo fica mais legivel
uint8_t digitos[] = {~0x3F, ~0x06, ~0x5B, ~0x4F,
                     ~0x66, ~0x6D, ~0x7D,
                     ~0x07, ~0x7F, ~0x67};

void GPIOSetup();

int main()
{
  GPIOSetup();

  while(1)
  {
      PORTB = 0x01;
      PORTD = digitos[5];
      _delay_ms(50);

      PORTD = 0x7F;
      //Serve para apagar os led 
      //antes de pular para o proximo digito
      //Se tirar ficara bugado

      PORTB = 0x02;
      PORTD = digitos[9];
      _delay_ms(50);

      PORTD = 0x7F; 
      //Serve para apagar os led 
      //antes de pular para o proximo digito
      //Se tirar ficara bugado
  }

  return 0;
}

void GPIOSetup()
{
  DDRB |= (1<<DIG_1) | (1<<DIG_2);
  DDRD |= 0x7F;
}
