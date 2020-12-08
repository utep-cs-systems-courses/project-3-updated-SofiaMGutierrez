
	.arch msp430g2553
	.p2align 1, 0
	.text

	.global buzz_advance_assembly

buzz_advance_assembly:
	;; note is stored in r12 since its sent by parameter
	
	sub #2, R1		; allocate memory for short
	mov #0, 0(R1)		; cmp_var = 0

	cmp r12, 0(R1)		; if(note < cmp_var), (note != cmp_var)
	jl fi			; jump to fi if note is not less than cmp_var
	add #100, r12		; if note < cmp_var then add 100 to note
	jmp end
fi:
	add #200, r12		; else add 200 to note
	jmp end

end:
	add #2, R1		; deallocate memory for short
	pop r0			; return value of r12
