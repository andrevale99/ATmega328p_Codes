.INCLUDE "./m328Pdef.inc"
.equ RESETAddr = 0x0000

.cseg

.org RESETAddr
    jmp RESET

RESET:
    jmp MAIN


.org 0x0064
MAIN:
    rjmp MAIN