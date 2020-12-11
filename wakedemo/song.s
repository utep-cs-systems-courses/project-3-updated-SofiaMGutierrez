
	.arch msp430g2553
	.p2align 1,0

	.data			; s is a static variable
s:
	.word 1			; s = 1

	.data
note1:
	.word 0			; note = 0;
	.text
jt:
	.word option1		; jt[0]
	.word option2		; jt[1]
	.word option3		; jt[2]
	
	.text
	.global song
song:
	;; range check on selector (s)
	cmp #3, &s		; s-3 doesn't borrow if s > 2
	jhs end			; jmp if s > 2

	;; index into jt
	mov &s, R12
	add R12, R12		; r12 = 2 bytes * s
	mov jt(R12), R0		; jmp jt[s]

	;; switch table options
	;; same order as in source code
option1:
	mov #1000, &note1
	add #1, &s
	jmp buzzer
	
option2:
	mov #2000, &note1
	add #1, &s
	jmp buzzer
option3:
	mov #3000, &note1
	mov #1, &s
	jmp buzzer
buzzer:
	mov &note1, R12		; play_buzzer(note1)
	call #play_buzzer
	jmp end
end:
	pop r0			; return to RA
