[bits 64]

GLOBAL	io_apic_enable
io_apic_enable:
	mov		ecx, 0x1b	; IA32_APIC_BASE_MSR
	rdmsr
	or		eax, 0x800	; IA32_APIC_BASE_MSR_ENABLE
	wrmsr
	ret

GLOBAL	outb
outb:	; rdi=[port], rsi=[value]
	mov	rdx, rdi	; port
	mov rax, rsi	; value
	out dx, al
	ret
GLOBAL	outw
outw:
	mov	rdx, rdi
	mov rax, rsi
	out dx, ax
	ret
GLOBAL	outl
outl:
	mov	rdx, rdi
	mov rax, rsi
	out dx, eax
	ret



GLOBAL	inb
inb:	; rdi=[port], al=return(value)
	mov	rdx, rdi	; port
	in	al, dx
	ret
GLOBAL	inw
inw:
	mov	rdx, rdi
	in	ax, dx
	ret
GLOBAL	inl
inl:
	mov	rdx, rdi
	in	eax, dx
	ret

GLOBAL io_wait
io_wait:
	out	0x80, al
	ret