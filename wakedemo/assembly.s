
	.arch msp430g2553
	.p2align 1,0
	.text

	.global decide

decide:
	;;decide_var is stored in r12 since its sent by parameter
	
	sub #2, r1		;allocate memory for new short variable, cmp_var
	mov #5, 0(r1)		;cmp_var = 5

	cmp r12, 0(r1)		;if(decide_var < cmp_var)
	jl fi			;N != V
	add #1, r12		;if decide_var < cmp_var then add 1 to note
	jmp end
fi:
	add #0, r12		;else add 0 to decide_var
	jmp end

end:
	add #2, r1		;deallocate memory for short
	pop r0			;return decide_var
