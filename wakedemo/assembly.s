
	.arch msp430g2553
	.p2align 1, 0
	.text

	.global buzz_advance_assembly ; makes it visible to other object files that are visible to it

buzz_advance_assembly:
	;; note is stored in r12 since its sent by parameter
	
	sub #2, R1		; allocate memory for short
	mov #0, 0(R1)		; cmp_var = 0

	cmp r12, 0(R1)		; if(note < cmp_var)
	jl fi			; N != V
	add #1, r12		; if note < cmp_var then add 1 to note
	jmp end
fi:
	add #0, r12		; else add 0 to note
	jmp end

end:
	add #2, R1		; deallocate memory for short
	;; note will be returned
	pop r0			; return the value of R12
