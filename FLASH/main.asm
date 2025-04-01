.INCLUDE "./m328Pdef.inc"

.cseg
.org 0x0000
	jmp RESET

RESET:
	lista: .db 0x01, 0x0F, 0x09, 0x0F, 0x05, 0x07
	
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

MAIN:

	;in r16, PIND ;Ler a as portas dos PORTD
    ;swap r16
    ;inc r16
    ;swap r16
	
	cpi ZL, LOW(lista<<1) + 6
	breq reset_Z
	jmp else_reset_z

reset_Z:
	ldi ZH, HIGH(lista<<1)
	ldi ZL, LOW(lista<<1)
	jmp end_reset_z
else_reset_z:
	lpm r16, Z+
	swap r16
	out PORTD, r16 ;Escreve no PORTD

	call delay

end_reset_z:
	rjmp MAIN

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