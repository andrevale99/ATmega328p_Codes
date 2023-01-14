;hello.asm
;  turns on an LED which is connected to PB5 (digital out 13)

.include "./m328Pdef.inc"
.cseg
.org 0x00

Setup:
	ldi r16,0b00000100
	out DDRD,r16
	out PortD,r16
    
Start:
	rjmp Start