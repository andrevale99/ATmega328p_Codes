.INCLUDE "./m328Pdef.inc"

.cseg
.org 0x00
	jmp Setup
.org UTXCaddr
	jmp USART_TX

Setup:
	; Inicializa a pilha 
	ldi r16, high(RAMEND)
	out SPH, r16
	ldi r16, low(RAMEND)
	out SPL, r16

	clr r16

USART_TX_SETUP:
	; Modo asynchronous
	; basta Escolher o Baud que deseja
	; e calcular o valor que deve colocar
	; no regisradores UBRR0H e UBRR0L 
	; UBRR0 = Fosc / (16*BAUD) - 1
	ldi r16, HIGH(103)
	stsUBRR0H, r16
	ldi r16, LOW(103)
	sts UBRR0L, r16

	clr r16

	ldi r16, (1<<TXEN0) | (1<<TXCIE0)
	sts UCSR0B, r16
	ldi r16, (1<<USBS0) | (3<<UCSZ00)
	sts UCSR0C, r16

	clr r16

	ldi r16, 'A'
	sts UDR0, r16

	sei

Start:
	rjmp Start

USART_TX:
	ldi r16, 'A'
	sts UDR0, r16
	reti
