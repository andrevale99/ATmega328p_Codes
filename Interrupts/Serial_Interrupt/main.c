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
 * @note O codigo utiliza de um botao no PB0 com PULL-UP o qual serve 
 * para ativar o comeco da transmissao, ao aterrar o PB0. Logica do codigo 
 * nos comentarios no codigo
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
volatile uint8_t idx = 0x00; //indice para percorrer o vetor
const char msg[] = "TX COMPLETE\n"; //vetor para transmitir na serial
volatile bool tx_em_acao = false; //booleano para indicar fim da operacao de trnasmissao
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

    for(;;)
    {
        //Caso pressione o botao, comece a transmissao
        //Ativa o bit de interrupcao de Verificar se o registrador
        //UDR0 esta vazio
        if(!(PINB & (1<<PINB0)) && !tx_em_acao)
            SetBit(UCSR0B, UDRIE0);
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
    
    ClrBit(DDRB, PB0);
    SetBit(PORTB, PB0);

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
    Desativa a interrupcao Data Empty
    Desativa a interrupcao complete*/
    SetBit(UCSR0B, TXEN0);
    ClrBit(UCSR0B, TXCIE0);
    ClrBit(UCSR0B, UDRIE0);

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
 * 
 * @note Entra nesta interrupcao quando
 * nao haver dado no registrador UDR0
 * 
 * @note Aqui ele comeca a operacao de transmissao
 * envia um dado para sinalizar algo, para depois 
 * desativar esta interrupcao e ativa a interrupcao de TX
*/
ISR(USART_UDRE_vect)
{
    if(!(PINB & (1<<PINB0)))
    {
        do
        {
            SetBit(PORTB, PB5);
        } while (!(PINB & (1<<PINB0)));
        ClrBit(PORTB, PB5);

        tx_em_acao = true;
        UDR0 = '&';
        idx = 0;
    }

    ClrBit(UCSR0B, UDRIE0);
    SetBit(UCSR0B, TXCIE0);
}

/**
 * @brief USART, Tx complete
 * 
 * @note Entra nesta interrupcao quando a 
 * transmissao for completa
 * 
 * @note Ao comecar a transmissao, percorre o vetor a
 * cada fim de transmissao, caso termine de percorrer o vetor
 * troca a flag booleana e sai da interrupcao antes
 * de enviar o '\0'
*/
ISR(USART_TX_vect)
{
    if(msg[idx]=='\0')
    {
        ClrBit(UCSR0B, TXCIE0);
        idx = 0;
        tx_em_acao = false;
        return;
    }
        
    UDR0 = msg[idx];
    ++idx;
}