	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	idx
	.section .bss
	.type	idx, @object
	.size	idx, 1
idx:
	.zero	1
.global	msg
	.section	.rodata
	.type	msg, @object
	.size	msg, 13
msg:
	.string	"TX COMPLETE\n"
.global	tx_em_acao
	.section .bss
	.type	tx_em_acao, @object
	.size	tx_em_acao, 1
tx_em_acao:
	.zero	1
	.text
.global	main
	.type	main, @function
main:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	call setup
/* #APP */
 ;  58 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L3:
	ldi r24,lo8(35)
	ldi r25,0
	movw r30,r24
	ld r24,Z
	mov r24,r24
	ldi r25,0
	andi r24,1
	clr r25
	or r24,r25
	brne .L3
	lds r25,tx_em_acao
	ldi r24,lo8(1)
	eor r24,r25
	tst r24
	breq .L3
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	ori r18,lo8(32)
	movw r30,r24
	st Z,r18
	rjmp .L3
	.size	main, .-main
.global	setup
	.type	setup, @function
setup:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	ldi r24,lo8(36)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(36)
	ldi r25,0
	ori r18,lo8(32)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(36)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(36)
	ldi r25,0
	andi r18,lo8(-2)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(37)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(37)
	ldi r25,0
	ori r18,lo8(1)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(103)
	ldi r25,0
	call USART_Init
	nop
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	setup, .-setup
.global	USART_Init
	.type	USART_Init, @function
USART_Init:
	push r28
	push r29
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	mov r18,r25
	clr r19
	ldi r24,lo8(-59)
	ldi r25,0
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-60)
	ldi r25,0
	ldd r18,Y+1
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	ori r18,lo8(8)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	andi r18,lo8(-65)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	andi r18,lo8(-33)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-62)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-62)
	ldi r25,0
	ori r18,lo8(8)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-62)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-62)
	ldi r25,0
	ori r18,lo8(2)
	movw r30,r24
	st Z,r18
	nop
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	USART_Init, .-USART_Init
.global	USART_Transmit
	.type	USART_Transmit, @function
USART_Transmit:
	push r28
	push r29
	push __zero_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
/* stack size = 3 */
.L__stack_usage = 3
	std Y+1,r24
	nop
.L7:
	ldi r24,lo8(-64)
	ldi r25,0
	movw r30,r24
	ld r24,Z
	mov r24,r24
	ldi r25,0
	andi r24,32
	clr r25
	or r24,r25
	breq .L7
	ldi r24,lo8(-58)
	ldi r25,0
	ldd r18,Y+1
	movw r30,r24
	st Z,r18
	nop
/* epilogue start */
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	USART_Transmit, .-USART_Transmit
.global	__vector_19
	.type	__vector_19, @function
__vector_19:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r24
	push r25
	push r30
	push r31
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
	ldi r24,lo8(35)
	ldi r25,0
	movw r30,r24
	ld r24,Z
	mov r24,r24
	ldi r25,0
	andi r24,1
	clr r25
	or r24,r25
	brne .L9
.L10:
	ldi r24,lo8(37)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(37)
	ldi r25,0
	ori r18,lo8(32)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(35)
	ldi r25,0
	movw r30,r24
	ld r24,Z
	mov r24,r24
	ldi r25,0
	andi r24,1
	clr r25
	or r24,r25
	breq .L10
	ldi r24,lo8(37)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(37)
	ldi r25,0
	andi r18,lo8(-33)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(1)
	sts tx_em_acao,r24
	ldi r24,lo8(-58)
	ldi r25,0
	ldi r18,lo8(38)
	movw r30,r24
	st Z,r18
	sts idx,__zero_reg__
.L9:
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	andi r18,lo8(-33)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	ori r18,lo8(64)
	movw r30,r24
	st Z,r18
	nop
/* epilogue start */
	pop r29
	pop r28
	pop r31
	pop r30
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_19, .-__vector_19
.global	__vector_20
	.type	__vector_20, @function
__vector_20:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r24
	push r25
	push r30
	push r31
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
	lds r24,idx
	mov r24,r24
	ldi r25,0
	subi r24,lo8(-(msg))
	sbci r25,hi8(-(msg))
	movw r30,r24
	ld r24,Z
	tst r24
	brne .L12
	ldi r24,lo8(-63)
	ldi r25,0
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-63)
	ldi r25,0
	andi r18,lo8(-65)
	movw r30,r24
	st Z,r18
	sts idx,__zero_reg__
	sts tx_em_acao,__zero_reg__
	rjmp .L11
.L12:
	lds r24,idx
	mov r24,r24
	ldi r25,0
	subi r24,lo8(-(msg))
	sbci r25,hi8(-(msg))
	movw r30,r24
	ld r18,Z
	ldi r24,lo8(-58)
	ldi r25,0
	movw r30,r24
	st Z,r18
	lds r24,idx
	subi r24,lo8(-(1))
	sts idx,r24
.L11:
/* epilogue start */
	pop r29
	pop r28
	pop r31
	pop r30
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_20, .-__vector_20
	.ident	"GCC: (GNU) 7.5.0"
.global __do_copy_data
.global __do_clear_bss
