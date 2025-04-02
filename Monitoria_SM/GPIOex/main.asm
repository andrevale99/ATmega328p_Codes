.INCLUDE "./m328Pdef.inc"

.def unidades = r0
.def dezenas = r1
.def centenas = r2
.def temp = r16

.dseg
	valor: .byte 3

.cseg
.org 0x0000
	jmp RESET

RESET:
	;	Inicializa e configura os vetores de interrupcao
	;trecho retirado do datasheet
	ldi r16, high(RAMEND)
	out SPH, r16
	ldi r16, low(RAMEND)
	out SPL, r16
	
	clr r16

    ldi r16, 0xF0
	out DDRD, r16
	clr r16

	cli

	ldi ZL, LOW(valor)
	ldi ZH, HIGH(valor)

	ldi temp, 12
	st Z+, temp

	ldi temp, 34
	st Z+, temp

	ldi temp, 56
	st Z, temp

	ldi ZL, LOW(valor)
	ldi ZH, HIGH(valor)

MAIN:
	ld temp, Z+

	cpi ZL, LOW(valor) + 4
	breq reset_pointer
	rjmp else_reset_pointer

reset_pointer:
	ldi ZL, LOW(valor)
	ldi ZH, HIGH(valor)
	rjmp MAIN

else_reset_pointer:
	call BinBCD

	swap centenas
	out PORTD, centenas
	call delay

	swap dezenas
	out PORTD, dezenas
	call delay

	swap unidades
	out PORTD, unidades
	call delay

	clr centenas
	clr dezenas
	clr unidades

	rjmp MAIN

BinBCD:
	cpi temp, 100
	brlo BinBCD_dezenas
	subi temp, 100
	inc centenas
	rjmp BinBCD

BinBCD_dezenas:
	cpi temp, 10
	brlo exit_BinBCD
	subi temp, 10
	inc dezenas
	rjmp BinBCD_dezenas

exit_BinBCD:
	mov unidades, temp
	clr temp
	ret

delay:
	ldi r17, 42
	ldi r18, 0
	ldi r19, 0
delay_loop:
	dec r19
	cpi r19, 0
	brne delay_loop

	dec r18
	cpi r18, 0
	brne delay_loop

	dec r17
	cpi r17, 0
	brne delay_loop

	ret