	.arch msp430g2553
	.p2align 1,0
state:
	.word 1			;
note:
	.byte 0			;
jt:
	.word case0		;
	.word case1		;
	.word case2		;
	.word case3		;
	.word default		;

	.global song
song:
	mov state, r12		;
	cmp #3, r12		;state-3
	jnc default
	add r12, r12		;
	mov jt(r12), r0		;

case1:
	mov #1000, &note	;
	add #1, &state		;
	jmp end			;
case2:
	mov #2000, &note	;
	add #1, &state		;
	jmp end			;
case3:
	move #3000, &note	;
	add #1, &state		;
	jmp end			;
default:
	add #0, &note		;
	jmp end			;
end:
	call #buzzer_set_period	;
	pop r0			;
