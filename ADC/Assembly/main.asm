.INCLUDE "./m328Pdef.inc"
.equ RESETAddr = 0x0000

.cseg

.org RESETAddr
    jmp RESET
.org OC1Baddr
    jmp TIMER_1_COMPB
.org ADCCaddr
    jmp ADC_INTERRUPT

RESET:
    ; Escreve o prescale de 16e6/1024
	;e o modo NORMAL do Timer 1
	clr r16
	sbr r16, (1<<CS12) | (1<<CS10)
	sts TCCR1B, r16 

    ; ldi r16, (1<<OCIE1B)
    ; sts TIMSK1, r16


	ldi r16, LOW(15625)  
	ldi r17, HIGH(15625)

	sts OCR1BH, r17 ;Escreve o valor de 15625 
	sts OCR1BL, r16 ;nos registradores MSB e LSB do comparador
	
	clr r16
	clr r17

    sbi DDRB, DDB5
	cbi PORTB, PB5

    ldi r16, (1<<REFS0)
    sts ADMUX, r16
    ; Habilita o ADC com a interrupcao
    ;com o prescale de 128
    ; ldi r16, (1<<ADIE) | (0x07<<ADPS0) | (1<<ADATE)
    ldi r16, 0xEF
    sts ADCSRA, r16
    ; Trigger no TIME_2_COMPARE_B
    ldi r16, (1<<ADTS2) | (1<<ADTS0)
    sts ADCSRB, r16

	clr r16

    sei

    jmp MAIN


.org 0x0064
MAIN:
    rjmp MAIN

TIMER_1_COMPB:
    ldi r16, $0
    sts TCNT1H, r16
    sts TCNT1L, r16

    clr r16

	reti

ADC_INTERRUPT:
    ldi r16, 0x20 
	in r17, PINB ;Ler a as portas dos PORTB
	eor r17, r16 ;Realiza a troca do pino PB5
	out PORTB, r17 ;Escreve no PORTB

    ldi r16, $0
    ldi r16, (1 << OCF1B)
    sts TIFR1, r16
    
    clr r16
	clr r17

    ldi r16, 0xEF
    sts ADCSRA, r16
    
    ldi r16, $0
    sts TCNT1H, r16
    sts TCNT1L, r16
    clr r16

    reti