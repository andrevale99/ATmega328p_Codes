.INCLUDE "./m328Pdef.inc"
.equ RESETAddr = 0x0000

.equ VAR_COMP = 33
.equ VAR_SRAM = 33

.dseg
    var: .byte 1


.cseg

.org RESETAddr
    jmp RESET

RESET:
    ldi r16, LOW(RAMEND)
    ldi r17, HIGH(RAMEND)

    sts SPH, r17
    sts SPL, r16

    clr r16
    clr r17

    ldi ZL, LOW(var)
    ldi ZH, HIGH(var)

    ldi r16, VAR_SRAM
    st Z, r16

    clr r16
    clr ZH
    clr ZL

    jmp MAIN


.org 0x0064
MAIN:
    ldi ZL, LOW(var)
    ldi ZH, HIGH(var)

    ld r16, Z

    cpi r16, VAR_COMP
    breq TESTE

    rjmp MAIN

TESTE:
    sbi PORTB, PB5

    rjmp MAIN