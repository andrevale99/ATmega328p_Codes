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
 * Utiliza um potenciometro para mudar a frequencia, lendo a
 * entrada analogica, e modificando o valor do OCR1A.
 * 
 * Uma forma de melhorar ainda mais o codigo, seria de utilizar a
 * interrupcao de vez a programacao procedural, mas como o pino PB1
 * esta no modo "assincrono", nao tem necessidade disso.
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
uint16_t freq_mod = 0x00; //Variavel que irar modificar a frequencia

//===================================================
//  PROTOTIPOS
//===================================================
void setup();

void adc_setup();
uint16_t adc_read(uint8_t pino);
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
        freq_mod = adc_read(0x00);
        OCR1A = 62500/4/(1+freq_mod);
        //Foi adicionado +1 para nao haver divisao por zero
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
    adc_setup();

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