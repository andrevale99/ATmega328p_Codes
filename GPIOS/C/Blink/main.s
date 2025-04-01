	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	setup
	.type	setup, @function
setup:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	sbi 0x4,5
	cbi 0x5,5
	ldi r30,lo8(-127)
	ldi r31,0
	ld r24,Z
	ori r24,lo8(8)
	st Z,r24
	ld r24,Z
	ori r24,lo8(4)
	st Z,r24
	ld r24,Z
	ori r24,lo8(1)
	st Z,r24
	ldi r30,lo8(111)
	ldi r31,0
	ld r24,Z
	ori r24,lo8(2)
	st Z,r24
	ldi r24,lo8(9)
	ldi r25,lo8(61)
	sts 136+1,r25
	sts 136,r24
/* epilogue start */
	ret
	.size	setup, .-setup
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call setup
/* #APP */
 ;  44 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L3:
	rjmp .L3
	.size	main, .-main
	.text
.global	__vector_11
	.type	__vector_11, @function
__vector_11:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r25
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 5 */
.L__stack_usage = 5
	in r24,0x5
	ldi r25,lo8(32)
	eor r24,r25
	out 0x5,r24
/* epilogue start */
	pop r25
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_11, .-__vector_11
	.ident	"GCC: (GNU) 7.5.0"
