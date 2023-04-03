.include "m328Pdef.inc"

.dseg
.org 0x0100
	v: .byte 4 

.cseg
.org 0x00

rjmp RESETaddr
reti ;INT0addr	; External Interrupt Request 0
reti ;INT1addr	; External Interrupt Request 1
reti ;PCI0addr	; Pin Change Interrupt Request 0
reti ;PCI1addr	; Pin Change Interrupt Request 0
reti ;PCI2addr	; Pin Change Interrupt Request 1
reti ;WDTaddr	; Watchdog Time-out Interrupt
reti ;OC2Aaddr	; Timer/Counter2 Compare Match A
reti ;OC2Baddr	; Timer/Counter2 Compare Match A
reti ;OVF2addr	; Timer/Counter2 Overflow
reti ;ICP1addr	; Timer/Counter1 Capture Event
reti ;OC1Aaddr	; Timer/Counter1 Compare Match A
reti ;OC1Baddr	; Timer/Counter1 Compare Match B
reti ;OVF1addr	; Timer/Counter1 Overflow
reti ;OC0Aaddr	; TimerCounter0 Compare Match A
reti ;OC0Baddr	; TimerCounter0 Compare Match B
reti ;OVF0addr	; Timer/Couner0 Overflow
reti ;SPIaddr	; SPI Serial Transfer Complete
reti ;URXCaddr	; USART Rx Complete
reti ;UDREaddr	; USART, Data Register Empty
reti ;UTXCaddr	; USART Tx Complete
reti ;ADCCaddr	; ADC Conversion Complete
reti ;ERDYaddr	; EEPROM Ready
reti ;ACIaddr	; Analog Comparator
reti ;TWIaddr	; Two-wire Serial Interface
reti ;SPMRaddr	; Store Program Memory Read

RESETaddr:
	;	Inicializa e configura os vetores de interrupcao
	;trecho retirado do datasheet
	ldi r16, high(RAMEND)
	out SPH, r16
	ldi r16, low(RAMEND)
	out SPL, r16
	
	ldi r16, 0xF0
	out DDRD, r16

	clr r16, 0x00
	out PORTD, r16

	clr r16

	rjmp Setup

Setup:


Loop:
	rjmp Loop
