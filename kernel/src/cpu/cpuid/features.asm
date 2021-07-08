[bits 64]

SECTION	.text

GLOBAL	cpu_enable_features
cpu_enable_features:
	push	rbp
	mov		rbp, rsp
	push	rbx
	; Enable Coprocessors (FPU and SSE)
	mov		rax, cr0
	and		rax, 0xfffffffffffffffb	; disable FPU emulation
	or		rax, 0x22				; enable monitoring coprocessor and numeric error
	mov		cr0, rax
	mov		rax, cr4
	; TODO enable XSAVE here
	or		rax, 0x0406b0			; enable OSFXSR, OSXMMEXCPT and others
	mov		cr4, rax	
	fninit
	; Finish
	pop		rbx
	pop		rbp
	ret