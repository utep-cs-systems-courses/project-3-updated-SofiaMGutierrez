
	.arch msp430g2553
	.p2align 1,0

	.data
s:
	.word 1			; static int s = 1

	.data 
n:
	.word 0			; static int n = 0

	.text
jt:
	.word option1		; jt[0]
	.word option2		; jt[1]
	.word option3		; jt[2]

	.text
	.global song
song:
	;; range check on selector (s)
	cmp #4, &s		; s-4 doesn't borrow if s>3
	jhs end			; jmp if s>3

	;; index into jt
	mov &s, r12
	add r12, r12		; r12 = 2 bytes * s
	mov jt(r12), r0		; jmp jt[s]

	;; switch table options
	;; same order as in source code
option1:
	mov #1000, &n
	add #1, &s
	jmp g
	
option2:
	mov #2000, &n
	add #1, &s
	jmp g
option3:
	mov #3000, &n
	mov #1, &s
	jmp g
g:
	mov &n, r12		; g(n)
	call #g
	jmp end
end:
	pop r0			; return to RA
