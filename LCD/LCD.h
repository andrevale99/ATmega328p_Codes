#ifndef LCD_H
#define LCD_H

/*
  Biblioteca criada baseado em:
  https://www.electronicwings.com/avr-atmega/interfacing-lcd-16x2-in-4-bit-mode-with-atmega-16-32-
  AVR e Arduino: Tecnicas de Projeto
  (Charles Borges de Lima; Marco V. M. Villaca)
*/

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define EN PD3 //Enable 
#define RS PD2  //RS
#define DDRx_LCD DDRD //DDRx em que os bits do~LCD estarao
#define PORTx_LCD PORTD //PORTx em que os bits do LCD estarao

#define WRITE 1
#define CMD 0

#define pulseEN() _delay_us(1) ;PORTx_LCD |= (1<<EN); \
                  _delay_us(1); PORTx_LCD &= ~(1<<EN); \
                  _delay_us(50);

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define SECOND_LINE 0xC0

#define ENTRY_MODE_SET 0x04
#define INCREMENT (ENTRY_MODE_SET | 0x02) // I
#define DECREMENT (ENTRY_MODE_SET | 0x00) // D
#define SHIFT_DISPLAY (ENTRY_MODE_SET | 0x01) // S

#define DISPLAY_CONTROL 0x08
#define DISPLAY_OFF (DISPLAY_CONTROL | 0x00) // D
#define DISPLAY_ON (DISPLAY_CONTROL | 0x04) // D
#define CURSOR_ON (DISPLAY_CONTROL | 0x02) // C
#define BLINK_CURSOR (DISPLAY_CONTROL | 0x01) // B

#define CURSOR_SHIFT 0x10
#define DISPLAY_SHIFT (CURSOR_SHIFT | 0x08) // S
#define CURSOR_MOVE (CURSOR_SHIFT | 0x00) // C
#define SHIFT_RIGHT (CURSOR_SHIFT | 0x04) // R
#define SHIFT_LEFT (CURSOR_SHIFT | 0x00) // L

#define FUNCTION_SET 0x20
#define BITS_8 (FUNCTION_SET | 0x00) // DL
#define BITS_4 (FUNCTION_SET | 0x01) // DL
#define LINES_1 (FUNCTION_SET | 0x00) // N
#define LINES_2 (FUNCTION_SET | 0x08) // N
#define FONT_5x8 (FUNCTION_SET | 0x00) // F
#define FONT_5x10 (FUNCTION_SET | 0x04) // F

#define SET_DDRAM 0x80

/**
* @brief Funcao para envio de comandos e escrita 
* 
* @param cmd -> O comando do LCD ou caractere que deseja escrever
* @param write_or_cmd -> Verificacao se sera algum comando ou 
*                         escrita no LCD
*
* @note Para ESCRITA write_or_cmd==1 (WRITE), caso deseja enviar 
* algum COMANDO write_or_cmd==0 (CMD)
*/
void LCD_cmd(uint8_t cmd, uint8_t write_or_cmd)
{
  PORTx_LCD =  (cmd & 0xF0); /* sending upper nibble */
	
  if(write_or_cmd == CMD)
    PORTx_LCD &= ~ (1<<RS);		/* RS=0, command reg. */
	else
    PORTx_LCD |=  (1<<RS);		/* RS=1, command reg. */
  
  pulseEN()

	_delay_us(200);

	PORTx_LCD = (cmd << 4);  /* sending lower nibble */
	pulseEN()

  if(write_or_cmd == WRITE)
    PORTx_LCD &= ~ (1<<RS);		/* RS=0, command reg. */

  _delay_ms(50);
}

/**
* @brief Inicializa o display LCD 16x2
* no protocolo de 4 bits
*/
void init_4bitsLCD()
{
  DDRx_LCD |= (1<<EN) | (1<<RS) | 0xFF;

  _delay_ms(100); //Estabilizacao do VCC do LCD (datasheet)
  pulseEN();
  _delay_ms(10);
  pulseEN();
  _delay_ms(10);

  LCD_cmd(RETURN_HOME, CMD); //
  LCD_cmd(BITS_4 | LINES_2, CMD); //interface de 4 bits 2 linhas (aqui se habilita as 2 linhas)
                                  //são enviados os 2 nibbles (0x2 e 0x8)
  LCD_cmd(CLEAR_DISPLAY, CMD); //limpa todo o display
  LCD_cmd(DISPLAY_ON | CURSOR_ON | BLINK_CURSOR, CMD); //mensagem aparente cursor inativo não piscando
  LCD_cmd(SET_DDRAM | 0x00, CMD); //inicializa cursor na primeira posição a esquerda - 1a linha
}

/**
 * @brief Funcao para escrever uma string no LCD
 * 
 * @param str -> Ponteiro de um vetor de char
 * @param size -> tamanho do vetor
*/
void writeLCD(const char *str, const uint8_t size)
{
  for(uint8_t idx=0; idx < size; ++idx)
    LCD_cmd(str[idx], WRITE);
}

#endif