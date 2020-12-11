
	.arch msp430g2553
	.p2align 1,0
	.text

	.data
state:
	.word 0			; state is a static variable (in ram)

	.data
note:
	.word 0			; note is a static variable (in ram)

	.text			; jt is constants (in flash)
jt:
	.word default		; jt[0]
	.word option0		; jt[1]
	.word option1		; jt[2]
	.word option2		; jt[3]
	.word option3		; jt[4]

	.global buzz_advance
buzz_advance:
	;; range check on selector (state)
	cmp #5, &state		; state-5 doesn't borrow if state>4
	jhs default		; jmp if s>3

	;; index into jt
	mov state, R12
	add R12, R12		; R12 = 2*state
	mov jt(r12), r0		; jmp jt[state]

option0:
	mov #1000, &note
	add #1, &state
	jmp function
	
option1:
	mov #2000, &note
	add #1, &state
	jmp function
	
option2:
	mov #3000, &note
	add #1, &state
	jmp function
	
option3:
	mov #4000, &note
	mov #0, &state
	jmp function
	
default:
	add #1, &state

function:
	mov &note, R12
	#play_buzzer(note)
	jmp end

end:
	pop r0
