	.file	"main.cpp"
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.section	.text._ZN7logtempD2Ev,"axG",@progbits,_ZN7logtempD5Ev,comdat
	.align 2
	.weak	_ZN7logtempD2Ev
	.type	_ZN7logtempD2Ev, @function
_ZN7logtempD2Ev:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	_ZN7logtempD2Ev, .-_ZN7logtempD2Ev
	.weak	_ZN7logtempD1Ev
	.set	_ZN7logtempD1Ev,_ZN7logtempD2Ev
	.globl	graphics
	.data
	.align 4
	.type	graphics, @object
	.size	graphics, 4
graphics:
	.long	1
	.section	.rodata
.LC0:
	.string	"core two "
.LC1:
	.string	"core three "
.LC2:
	.string	"core four "
.LC3:
	.string	"graphics one"
.LC4:
	.string	"graphics two"
.LC5:
	.string	"graphics three"
.LC6:
	.string	"graphics four"
	.text
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$2, graphics(%rip)
	movl	$1, -16(%rbp)
	leaq	-11(%rbp), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
	call	_ZlsIA10_cEO7logtempS2_RKT_
	leaq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZlsI2slEO7logtempS2_RKT_
	leaq	-11(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
	leaq	-10(%rbp), %rax
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZlsIA12_cEO7logtempS2_RKT_
	leaq	-10(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
	leaq	-9(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	_ZlsIA11_cEO7logtempS2_RKT_
	leaq	-9(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
	movl	graphics(%rip), %eax
	testl	%eax, %eax
	jg	.L4
	leaq	-8(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	_ZlsIA13_cEO7logtempS2_RKT_
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L4:
	movl	graphics(%rip), %eax
	cmpl	$1, %eax
	jg	.L5
	leaq	-7(%rbp), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	call	_ZlsIA13_cEO7logtempS2_RKT_
	leaq	-7(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L5:
	movl	graphics(%rip), %eax
	cmpl	$2, %eax
	jg	.L6
	leaq	-6(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	_ZlsIA15_cEO7logtempS2_RKT_
	leaq	-6(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L6:
	movl	graphics(%rip), %eax
	cmpl	$3, %eax
	jg	.L7
	leaq	-5(%rbp), %rax
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	_ZlsIA14_cEO7logtempS2_RKT_
	leaq	-5(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L7:
	movl	$1, graphics(%rip)
	movl	graphics(%rip), %eax
	testl	%eax, %eax
	jg	.L8
	leaq	-4(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	_ZlsIA13_cEO7logtempS2_RKT_
	leaq	-4(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L8:
	movl	graphics(%rip), %eax
	cmpl	$1, %eax
	jg	.L9
	leaq	-3(%rbp), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	call	_ZlsIA13_cEO7logtempS2_RKT_
	leaq	-3(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L9:
	movl	graphics(%rip), %eax
	cmpl	$2, %eax
	jg	.L10
	leaq	-2(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	_ZlsIA15_cEO7logtempS2_RKT_
	leaq	-2(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L10:
	movl	graphics(%rip), %eax
	cmpl	$3, %eax
	jg	.L11
	leaq	-1(%rbp), %rax
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	_ZlsIA14_cEO7logtempS2_RKT_
	leaq	-1(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7logtempD1Ev
.L11:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	main, .-main
	.section	.text._ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_,"axG",@progbits,_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_,comdat
	.weak	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	.type	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_, @function
_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_, .-_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	.section	.text._ZlsIA10_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA10_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA10_cEO7logtempS2_RKT_
	.type	_ZlsIA10_cEO7logtempS2_RKT_, @function
_ZlsIA10_cEO7logtempS2_RKT_:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	_ZlsIA10_cEO7logtempS2_RKT_, .-_ZlsIA10_cEO7logtempS2_RKT_
	.section	.text._ZlsI2slEO7logtempS2_RKT_,"axG",@progbits,_ZlsI2slEO7logtempS2_RKT_,comdat
	.weak	_ZlsI2slEO7logtempS2_RKT_
	.type	_ZlsI2slEO7logtempS2_RKT_, @function
_ZlsI2slEO7logtempS2_RKT_:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	_ZlsI2slEO7logtempS2_RKT_, .-_ZlsI2slEO7logtempS2_RKT_
	.section	.text._ZlsIA12_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA12_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA12_cEO7logtempS2_RKT_
	.type	_ZlsIA12_cEO7logtempS2_RKT_, @function
_ZlsIA12_cEO7logtempS2_RKT_:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	_ZlsIA12_cEO7logtempS2_RKT_, .-_ZlsIA12_cEO7logtempS2_RKT_
	.section	.text._ZlsIA11_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA11_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA11_cEO7logtempS2_RKT_
	.type	_ZlsIA11_cEO7logtempS2_RKT_, @function
_ZlsIA11_cEO7logtempS2_RKT_:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	_ZlsIA11_cEO7logtempS2_RKT_, .-_ZlsIA11_cEO7logtempS2_RKT_
	.section	.text._ZlsIA13_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA13_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA13_cEO7logtempS2_RKT_
	.type	_ZlsIA13_cEO7logtempS2_RKT_, @function
_ZlsIA13_cEO7logtempS2_RKT_:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	_ZlsIA13_cEO7logtempS2_RKT_, .-_ZlsIA13_cEO7logtempS2_RKT_
	.section	.text._ZlsIA15_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA15_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA15_cEO7logtempS2_RKT_
	.type	_ZlsIA15_cEO7logtempS2_RKT_, @function
_ZlsIA15_cEO7logtempS2_RKT_:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	_ZlsIA15_cEO7logtempS2_RKT_, .-_ZlsIA15_cEO7logtempS2_RKT_
	.section	.text._ZlsIA14_cEO7logtempS2_RKT_,"axG",@progbits,_ZlsIA14_cEO7logtempS2_RKT_,comdat
	.weak	_ZlsIA14_cEO7logtempS2_RKT_
	.type	_ZlsIA14_cEO7logtempS2_RKT_, @function
_ZlsIA14_cEO7logtempS2_RKT_:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIR7logtempEONSt16remove_referenceIT_E4typeEOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	_ZlsIA14_cEO7logtempS2_RKT_, .-_ZlsIA14_cEO7logtempS2_RKT_
	.section	.rodata
	.align 4
	.type	_ZL4core, @object
	.size	_ZL4core, 4
_ZL4core:
	.long	1
	.ident	"GCC: (GNU) 4.8.3"
	.section	.note.GNU-stack,"",@progbits
