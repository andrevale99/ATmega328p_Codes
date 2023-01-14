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

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

//===================================================
//  VARIAVEIS
//===================================================

//===================================================
//  PROTOTIPOS
//===================================================
void setup();

void adc_setup();
uint16_t adc_read(uint8_t pino);

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
//===================================================
//  MAIN
//===================================================
int main()
{
    setup();

    for(;;)
    {
        USART_Transmit(adc_read(0x00));
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
    SetBit(DDRB, DDB1);
    ClrBit(PORTB, PB1);

    adc_setup();

    //SetBit(TCCR1A, COM1A1);
    SetBit(TCCR1A, COM1A0);
    SetBit(TCCR1A, WGM10);

    SetBit(TCCR1B, WGM13);
    SetBit(TCCR1B, CS12);
    //SetBit(TCCR1B, CS10);

    OCR1A = 30000;
}

/**
 * @brief Inicializacao do ADC
 * 
 * @note Ativa o ADC com o prescale de 16e6/128 e
 * referencia no AVCC/AREF 
*/
void adc_setup()
{
    SetBit(ADCSRA, ADEN);
    SetBit(ADCSRA, ADPS2);
    SetBit(ADCSRA, ADPS1);
    SetBit(ADCSRA, ADPS0);
        
    SetBit(ADMUX, REFS0);
}

/**
 * @brief Funcao para pegar o valor do adc
 * @param pino Pino que deseja ler
 * @return Valor da conversao ADC em um valor de 16 bits
 * 
 * @note Retorna um valor de 16 bits pela facilidade,
 * ja que a resolucao do arduino e de 10 bits
*/
uint16_t adc_read(uint8_t pino)
{
    static uint8_t adc_LSB; 
    static uint8_t adc_MSB;

    ADMUX |= pino;

    SetBit(ADCSRA, ADSC);

    while(!(ADCSRA &= ~(1<<ADIF)));

    SetBit(ADCSRA, ADIF);

    adc_LSB = ADCL;
    adc_MSB = ADCH;

    SetBit(ADCSRA, ADSC);

    return (adc_MSB<<8) | adc_LSB;
}

/**
 * @brief Inicializacao do USART
 * @param ubrr Valor calculado do baud rate
 * 
 * @note A definicao MYUBRR ja faz o calculo (datasheet)
 * e inicializa somento o TX, para o RX (1<<RXEN0) no
 * registrador UCSR0B
*/
void USART_Init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*Enable transmitter */
    SetBit(UCSR0B, TXEN0);
    /* Set frame format: 8data, 2stop bit */
    SetBit(UCSR0C, USBS0);
    SetBit(UCSR0C, UCSZ00);
}

/**
 * @brief Transmissao de um byte pelo USART0
 * @param data caractere
*/
void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0))) 
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}