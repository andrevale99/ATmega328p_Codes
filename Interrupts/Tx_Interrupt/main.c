/**
 * @author Andre Menezes de Freitas Vale
 * 
 * @brief Algoritmo que utiliza das interrupcoes para enviar
 * dados pela serial USART0 do ATmega328p
 * 
 * @note A Funcao USART_transmit nao utiliza da interrupcao
 * para enviar o dado, esta aqui pq copiei e colei caso alguem necessite
 * utiliza-la e esta com preguica de pegar do datasheet :)
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
volatile uint8_t cnt = 0x00;

//===================================================
//  PROTOTIPOS
//===================================================
void setup();

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);

ISR(USART_UDRE_vect);
ISR(USART_TX_vect);
//===================================================
//  MAIN
//===================================================
int main()
{
    setup();
    sei();

    UDR0 = 0xAA;

    for(;;)
    {
        _delay_ms(1000);
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
    SetBit(DDRB, DDB5);
    USART_Init(MYUBRR);
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

    /*Enable transmitter 
    Enable interrupt Data Empty
    Enable Transmitter complete*/
    SetBit(UCSR0B, TXEN0);
    SetBit(UCSR0B, TXCIE0);
    SetBit(UCSR0B, UDRIE0);

    /* Set frame format: 8data, 2stop bit */
    SetBit(UCSR0C, USBS0);
    SetBit(UCSR0C, UCSZ00);
}

/**
 * @brief Transmissao de um byte pelo USART0
 * @param data caractere
 * 
 * @note Essa funcao é utilizada quando nao for utilizada
 * as interrupcoes para envio de dado
*/
void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0))) 
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

/**
 * @brief USART, data register empty
*/
ISR(USART_UDRE_vect)
{
    ++cnt;
    UDR0 = cnt;
}

/**
 * @brief USART, Tx complete
*/
ISR(USART_TX_vect)
{
    ToggleBit(PORTB, PB5);
}