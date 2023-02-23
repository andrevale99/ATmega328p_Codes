#include "LCD.h"

void inic_LCD_4bits()
{
	ClrBit(CONTR_LCD,RS);
	ClrBit(CONTR_LCD,E);

	_delay_ms(20);

	#if (nibble_dados)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;
	#else
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;
	#endif

	pulso_enable();
	_delay_ms(5);
	pulso_enable();
	_delay_us(200);
	pulso_enable();

	#if (nibble_dados)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;
	#else
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
	#endif
	
	pulso_enable();
	cmd_LCD(0x28, 0);

	cmd_LCD(0x08,0); //desliga o display
	cmd_LCD(0x01,0); //limpa todo o displayI
	cmd_LCD(0x0F,0); //mensagem aparente cursor inativo não piscando
	cmd_LCD(0x80,0); //inicializa cursor na primeira posição a esquerda - 1a linha

}

void cmd_LCD(unsigned char c, char cd)
{
	if(cd==0) //instrução
		ClrBit(CONTR_LCD,RS);
	else //caractere
		SetBit(CONTR_LCD,RS);

	#if (nibble_dados )//compila o código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F)|(0xF0 & c);
	#else //compila o código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);
	#endif

	pulso_enable();

	#if (nibble_dados) //compila o código para os
		DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));
	#else
		DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
	#endif

	pulso_enable();

	if((cd==0) && (c<4))
		_delay_ms(2);
}


void escreve_LCD(char *c)
{
	for (; *c!=0;c++) cmd_LCD(*c,1);
}
