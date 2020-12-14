
	.arch msp430g2553
	.p2align 1,0
	.text			;jt is constants (in flash)
	
jt:
	.word option0		;jt[0]
	.word option1		;jt[1]
	.word option2		;jt[2]
	
	.global buzz_assembly
	
buzz_assembly:
	;; parameters contain the variable state = 0
	
	sub #2, r1		;allocate space for a new short variable, note
	mov #0, 0(r1)		;note = 0
	
	cmp #3, r12		;state-3 doesn't borrow if state>2
	jhs end			;jmp if state>2

	cmp #0, r12		;does borrow if state<0
	jl end			;jmp if state<0
	
	add r12, r12		;r12=2*state
	mov jt(r12), r0		;jmp jt[state]

option0:
	mov #400, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end

option1:
	mov #500, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end

option2:
	mov #600, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end
	
end:
	add #2, r1
	pop r0
