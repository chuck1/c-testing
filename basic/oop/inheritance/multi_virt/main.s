	.file	"main.cpp"
	.section	.text._ZN1E3fooEv,"axG",@progbits,_ZN1E3fooEv,comdat
	.align 2
	.weak	_ZN1E3fooEv
	.type	_ZN1E3fooEv, @function
_ZN1E3fooEv:
.LFB9:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	_ZN1E3fooEv, .-_ZN1E3fooEv
	.section	.text._ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev
	.type	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev, @function
_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev:
.LFB15:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev, .-_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC1Ev
	.set	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC1Ev,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev
	.section	.text._ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev,"axG",@progbits,_ZN1BII1CII1DIIEE1EEES2_S3_EEC5Ev,comdat
	.align 2
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev
	.type	_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev, @function
_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev:
.LFB17:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EEC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1BII1CII1DIIEE1EEES2_S3_EE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev, .-_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EEC1Ev
	.set	_ZN1BII1CII1DIIEE1EEES2_S3_EEC1Ev,_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev
	.section	.text._ZN1CII1DIIEE1EEEC2Ev,"axG",@progbits,_ZN1CII1DIIEE1EEEC5Ev,comdat
	.align 2
	.weak	_ZN1CII1DIIEE1EEEC2Ev
	.type	_ZN1CII1DIIEE1EEEC2Ev, @function
_ZN1CII1DIIEE1EEEC2Ev:
.LFB19:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1CII1DIIEE1EEES2_S3_EEC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1CII1DIIEE1EEE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	_ZN1CII1DIIEE1EEEC2Ev, .-_ZN1CII1DIIEE1EEEC2Ev
	.weak	_ZN1CII1DIIEE1EEEC1Ev
	.set	_ZN1CII1DIIEE1EEEC1Ev,_ZN1CII1DIIEE1EEEC2Ev
	.section	.text._ZN1CII1DIIEE1EEED2Ev,"axG",@progbits,_ZN1CII1DIIEE1EEED5Ev,comdat
	.align 2
	.weak	_ZN1CII1DIIEE1EEED2Ev
	.type	_ZN1CII1DIIEE1EEED2Ev, @function
_ZN1CII1DIIEE1EEED2Ev:
.LFB22:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1CII1DIIEE1EEE+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L12
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	_ZN1CII1DIIEE1EEED2Ev, .-_ZN1CII1DIIEE1EEED2Ev
	.weak	_ZN1CII1DIIEE1EEED1Ev
	.set	_ZN1CII1DIIEE1EEED1Ev,_ZN1CII1DIIEE1EEED2Ev
	.section	.text._ZN1CII1DIIEE1EEED0Ev,"axG",@progbits,_ZN1CII1DIIEE1EEED5Ev,comdat
	.align 2
	.weak	_ZN1CII1DIIEE1EEED0Ev
	.type	_ZN1CII1DIIEE1EEED0Ev, @function
_ZN1CII1DIIEE1EEED0Ev:
.LFB24:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1CII1DIIEE1EEED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	_ZN1CII1DIIEE1EEED0Ev, .-_ZN1CII1DIIEE1EEED0Ev
	.section	.text._ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev
	.type	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev, @function
_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev:
.LFB28:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev, .-_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev
	.weak	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC1Ev
	.set	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC1Ev,_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev
	.section	.text._ZN1BII1DIIEEEEC2Ev,"axG",@progbits,_ZN1BII1DIIEEEEC5Ev,comdat
	.align 2
	.weak	_ZN1BII1DIIEEEEC2Ev
	.type	_ZN1BII1DIIEEEEC2Ev, @function
_ZN1BII1DIIEEEEC2Ev:
.LFB30:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EEC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1BII1DIIEEEE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	_ZN1BII1DIIEEEEC2Ev, .-_ZN1BII1DIIEEEEC2Ev
	.weak	_ZN1BII1DIIEEEEC1Ev
	.set	_ZN1BII1DIIEEEEC1Ev,_ZN1BII1DIIEEEEC2Ev
	.section	.text._ZN1DIIEEC2Ev,"axG",@progbits,_ZN1DIIEEC5Ev,comdat
	.align 2
	.weak	_ZN1DIIEEC2Ev
	.type	_ZN1DIIEEC2Ev, @function
_ZN1DIIEEC2Ev:
.LFB32:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1DIIEEEEC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1DIIEE+16, (%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	_ZN1DIIEEC2Ev, .-_ZN1DIIEEC2Ev
	.weak	_ZN1DIIEEC1Ev
	.set	_ZN1DIIEEC1Ev,_ZN1DIIEEC2Ev
	.section	.text._ZN1DIIEED2Ev,"axG",@progbits,_ZN1DIIEED5Ev,comdat
	.align 2
	.weak	_ZN1DIIEED2Ev
	.type	_ZN1DIIEED2Ev, @function
_ZN1DIIEED2Ev:
.LFB35:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1DIIEE+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1DIIEEEED2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L25
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L25:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	_ZN1DIIEED2Ev, .-_ZN1DIIEED2Ev
	.weak	_ZN1DIIEED1Ev
	.set	_ZN1DIIEED1Ev,_ZN1DIIEED2Ev
	.section	.text._ZN1DIIEED0Ev,"axG",@progbits,_ZN1DIIEED5Ev,comdat
	.align 2
	.weak	_ZN1DIIEED0Ev
	.type	_ZN1DIIEED0Ev, @function
_ZN1DIIEED0Ev:
.LFB37:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1DIIEED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	_ZN1DIIEED0Ev, .-_ZN1DIIEED0Ev
	.section	.text._ZN1EC2Ev,"axG",@progbits,_ZN1EC5Ev,comdat
	.align 2
	.weak	_ZN1EC2Ev
	.type	_ZN1EC2Ev, @function
_ZN1EC2Ev:
.LFB38:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1CII1DIIEE1EEEC2Ev
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZN1DIIEEC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1E+16, (%rax)
	movq	-8(%rbp), %rax
	movq	$_ZTV1E+48, 8(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
.L30:
	.cfi_endproc
.LFE38:
	.size	_ZN1EC2Ev, .-_ZN1EC2Ev
	.weak	_ZN1EC1Ev
	.set	_ZN1EC1Ev,_ZN1EC2Ev
	.text
.globl main
	.type	main, @function
main:
.LFB10:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	movl	$16, %edi
	.cfi_offset 3, -24
	call	_Znwm
	movq	%rax, %rbx
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_ZN1EC1Ev
.L34:
	movq	%rbx, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv
	movl	$0, %eax
	addq	$24, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	main, .-main
	.section	.text._ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev
	.type	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev, @function
_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev:
.LFB41:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE+16, (%rax)
	movl	$0, %eax
	testb	%al, %al
	je	.L39
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L39:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev, .-_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED1Ev
	.set	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED1Ev,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev
	.section	.text._ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev
	.type	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev, @function
_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev:
.LFB43:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev, .-_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev
	.section	.text._ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev,"axG",@progbits,_ZN1BII1CII1DIIEE1EEES2_S3_EED5Ev,comdat
	.align 2
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev
	.type	_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev, @function
_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev:
.LFB45:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1BII1CII1DIIEE1EEES2_S3_EE+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L46
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L46:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev, .-_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EED1Ev
	.set	_ZN1BII1CII1DIIEE1EEES2_S3_EED1Ev,_ZN1BII1CII1DIIEE1EEES2_S3_EED2Ev
	.section	.text._ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev,"axG",@progbits,_ZN1BII1CII1DIIEE1EEES2_S3_EED5Ev,comdat
	.align 2
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev
	.type	_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev, @function
_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev:
.LFB47:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1CII1DIIEE1EEES2_S3_EED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev, .-_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev
	.section	.text._ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev
	.type	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev, @function
_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev:
.LFB49:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE+16, (%rax)
	movl	$0, %eax
	testb	%al, %al
	je	.L53
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L53:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev, .-_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev
	.weak	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED1Ev
	.set	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED1Ev,_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev
	.section	.text._ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED5Ev,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev
	.type	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev, @function
_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev:
.LFB51:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev, .-_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev
	.section	.text._ZN1BII1DIIEEEED2Ev,"axG",@progbits,_ZN1BII1DIIEEEED5Ev,comdat
	.align 2
	.weak	_ZN1BII1DIIEEEED2Ev
	.type	_ZN1BII1DIIEEEED2Ev, @function
_ZN1BII1DIIEEEED2Ev:
.LFB53:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1BII1DIIEEEE+16, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L60
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L60:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	_ZN1BII1DIIEEEED2Ev, .-_ZN1BII1DIIEEEED2Ev
	.weak	_ZN1BII1DIIEEEED1Ev
	.set	_ZN1BII1DIIEEEED1Ev,_ZN1BII1DIIEEEED2Ev
	.section	.text._ZN1BII1DIIEEEED0Ev,"axG",@progbits,_ZN1BII1DIIEEEED5Ev,comdat
	.align 2
	.weak	_ZN1BII1DIIEEEED0Ev
	.type	_ZN1BII1DIIEEEED0Ev, @function
_ZN1BII1DIIEEEED0Ev:
.LFB55:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1DIIEEEED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	_ZN1BII1DIIEEEED0Ev, .-_ZN1BII1DIIEEEED0Ev
	.section	.text._ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv,"axG",@progbits,_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv,comdat
	.align 2
	.weak	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv
	.type	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv, @function
_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv:
.LFB56:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	movq	%rdi, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L65
	.cfi_offset 3, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	movl	$0, %r13d
	jmp	.L66
.L65:
	movq	-40(%rbp), %rax
	movl	$0, %ecx
	movl	$_ZTI1E, %edx
	movl	$_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, %esi
	movq	%rax, %rdi
	call	__dynamic_cast
	movq	%rax, %r13
.L66:
	cmpq	$0, -40(%rbp)
	jne	.L67
	movl	$0, %r12d
	jmp	.L68
.L67:
	movq	-40(%rbp), %rax
	movq	$-2, %rcx
	movl	$_ZTI1DIIEE, %edx
	movl	$_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, %esi
	movq	%rax, %rdi
	call	__dynamic_cast
	movq	%rax, %r12
.L68:
	cmpq	$0, -40(%rbp)
	jne	.L69
	movl	$0, %ebx
	jmp	.L70
.L69:
	movq	-40(%rbp), %rax
	movl	$0, %ecx
	movl	$_ZTI1CII1DIIEE1EEE, %edx
	movl	$_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, %esi
	movq	%rax, %rdi
	call	__dynamic_cast
	movq	%rax, %rbx
.L70:
	cmpq	$0, -40(%rbp)
	jne	.L71
	movl	$0, %eax
	jmp	.L72
.L71:
	movq	-40(%rbp), %rax
	movl	$0, %ecx
	movl	$_ZTI1BII1CII1DIIEE1EEES2_S3_EE, %edx
	movl	$_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, %esi
	movq	%rax, %rdi
	call	__dynamic_cast
.L72:
	movq	%r13, %rcx
	movq	%r12, %rdx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv, .-_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE4callEv
	.section	.text._Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_,"axG",@progbits,_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_,comdat
	.weak	_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_
	.type	_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_, @function
_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_:
.LFB57:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L75
	movl	$4, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rdx
	movl	$0, (%rdx)
	movl	$0, %edx
	movl	$_ZTIi, %esi
	movq	%rax, %rdi
	call	__cxa_throw
.L75:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_, .-_Z6__callI12dispatch_fooP1BII1CII1DIIEE1EEES4_S5_EEIPS6_PS4_PS5_EEvT0_DpT1_
	.section	.text._ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_,"axG",@progbits,_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_,comdat
	.weak	_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_
	.type	_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_, @function
_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_:
.LFB58:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_, .-_ZN12dispatch_foo4callI1BII1CII1DIIEE1EEES4_S5_EEEEvPT_
	.section	.text._Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_,"axG",@progbits,_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_,comdat
	.weak	_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_
	.type	_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_, @function
_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_:
.LFB59:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L80
	movl	$4, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rdx
	movl	$0, (%rdx)
	movl	$0, %edx
	movl	$_ZTIi, %esi
	movq	%rax, %rdi
	call	__cxa_throw
.L80:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_, .-_Z6__callI12dispatch_fooP1CII1DIIEE1EEEIPS3_PS4_EEvT0_DpT1_
	.section	.text._ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv,"axG",@progbits,_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv,comdat
	.align 2
	.weak	_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv
	.type	_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv, @function
_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv:
.LFB60:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv, .-_ZN1BII1CII1DIIEE1EEES2_S3_EE3fooEv
	.section	.text._ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_,"axG",@progbits,_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_,comdat
	.weak	_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_
	.type	_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_, @function
_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_:
.LFB61:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1CII1DIIEE1EEE3fooEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_, .-_ZN12dispatch_foo4callI1CII1DIIEE1EEEEEvPT_
	.section	.text._Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_,"axG",@progbits,_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_,comdat
	.weak	_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_
	.type	_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_, @function
_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_:
.LFB62:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L87
	movl	$4, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rdx
	movl	$0, (%rdx)
	movl	$0, %edx
	movl	$_ZTIi, %esi
	movq	%rax, %rdi
	call	__cxa_throw
.L87:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN12dispatch_foo4callI1DIIEEEEvPT_
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_, .-_Z6__callI12dispatch_fooP1DIIEEIP1EEEvT0_DpT1_
	.section	.text._ZN1CII1DIIEE1EEE3fooEv,"axG",@progbits,_ZN1CII1DIIEE1EEE3fooEv,comdat
	.align 2
	.weak	_ZN1CII1DIIEE1EEE3fooEv
	.type	_ZN1CII1DIIEE1EEE3fooEv, @function
_ZN1CII1DIIEE1EEE3fooEv:
.LFB63:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	_ZN1CII1DIIEE1EEE3fooEv, .-_ZN1CII1DIIEE1EEE3fooEv
	.section	.text._ZN12dispatch_foo4callI1DIIEEEEvPT_,"axG",@progbits,_ZN12dispatch_foo4callI1DIIEEEEvPT_,comdat
	.weak	_ZN12dispatch_foo4callI1DIIEEEEvPT_
	.type	_ZN12dispatch_foo4callI1DIIEEEEvPT_, @function
_ZN12dispatch_foo4callI1DIIEEEEvPT_:
.LFB64:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1DIIEE3fooEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	_ZN12dispatch_foo4callI1DIIEEEEvPT_, .-_ZN12dispatch_foo4callI1DIIEEEEvPT_
	.section	.text._Z6__callI12dispatch_fooP1EIEEvT0_DpT1_,"axG",@progbits,_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_,comdat
	.weak	_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_
	.type	_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_, @function
_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_:
.LFB65:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L94
	movl	$4, %edi
	call	__cxa_allocate_exception
	movq	%rax, %rdx
	movl	$0, (%rdx)
	movl	$0, %edx
	movl	$_ZTIi, %esi
	movq	%rax, %rdi
	call	__cxa_throw
.L94:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN12dispatch_foo4callI1EEEvPT_
	call	_Z6__callI12dispatch_fooEvv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_, .-_Z6__callI12dispatch_fooP1EIEEvT0_DpT1_
	.section	.text._ZN1DIIEE3fooEv,"axG",@progbits,_ZN1DIIEE3fooEv,comdat
	.align 2
	.weak	_ZN1DIIEE3fooEv
	.type	_ZN1DIIEE3fooEv, @function
_ZN1DIIEE3fooEv:
.LFB66:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	_ZN1DIIEE3fooEv, .-_ZN1DIIEE3fooEv
	.section	.text._ZN12dispatch_foo4callI1EEEvPT_,"axG",@progbits,_ZN12dispatch_foo4callI1EEEvPT_,comdat
	.weak	_ZN12dispatch_foo4callI1EEEvPT_
	.type	_ZN12dispatch_foo4callI1EEEvPT_, @function
_ZN12dispatch_foo4callI1EEEvPT_:
.LFB67:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1E3fooEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	_ZN12dispatch_foo4callI1EEEvPT_, .-_ZN12dispatch_foo4callI1EEEvPT_
	.section	.text._Z6__callI12dispatch_fooEvv,"axG",@progbits,_Z6__callI12dispatch_fooEvv,comdat
	.weak	_Z6__callI12dispatch_fooEvv
	.type	_Z6__callI12dispatch_fooEvv, @function
_Z6__callI12dispatch_fooEvv:
.LFB68:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	_Z6__callI12dispatch_fooEvv, .-_Z6__callI12dispatch_fooEvv
	.weak	_ZTV1E
	.section	.rodata._ZTV1E,"aG",@progbits,_ZTV1E,comdat
	.align 32
	.type	_ZTV1E, @object
	.size	_ZTV1E, 64
_ZTV1E:
	.quad	0
	.quad	_ZTI1E
	.quad	_ZN1ED1Ev
	.quad	_ZN1ED0Ev
	.quad	-8
	.quad	_ZTI1E
	.quad	_ZThn8_N1ED1Ev
	.quad	_ZThn8_N1ED0Ev
	.weak	_ZTV1DIIEE
	.section	.rodata._ZTV1DIIEE,"aG",@progbits,_ZTV1DIIEE,comdat
	.align 32
	.type	_ZTV1DIIEE, @object
	.size	_ZTV1DIIEE, 32
_ZTV1DIIEE:
	.quad	0
	.quad	_ZTI1DIIEE
	.quad	_ZN1DIIEED1Ev
	.quad	_ZN1DIIEED0Ev
	.weak	_ZTV1BII1DIIEEEE
	.section	.rodata._ZTV1BII1DIIEEEE,"aG",@progbits,_ZTV1BII1DIIEEEE,comdat
	.align 32
	.type	_ZTV1BII1DIIEEEE, @object
	.size	_ZTV1BII1DIIEEEE, 32
_ZTV1BII1DIIEEEE:
	.quad	0
	.quad	_ZTI1BII1DIIEEEE
	.quad	_ZN1BII1DIIEEEED1Ev
	.quad	_ZN1BII1DIIEEEED0Ev
	.weak	_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.section	.rodata._ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE,"aG",@progbits,_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE,comdat
	.align 32
	.type	_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE, @object
	.size	_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE, 32
_ZTV1AI12dispatch_fooI1BII1DIIEEEES3_EE:
	.quad	0
	.quad	_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.quad	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED1Ev
	.quad	_ZN1AI12dispatch_fooI1BII1DIIEEEES3_EED0Ev
	.weak	_ZTV1CII1DIIEE1EEE
	.section	.rodata._ZTV1CII1DIIEE1EEE,"aG",@progbits,_ZTV1CII1DIIEE1EEE,comdat
	.align 32
	.type	_ZTV1CII1DIIEE1EEE, @object
	.size	_ZTV1CII1DIIEE1EEE, 32
_ZTV1CII1DIIEE1EEE:
	.quad	0
	.quad	_ZTI1CII1DIIEE1EEE
	.quad	_ZN1CII1DIIEE1EEED1Ev
	.quad	_ZN1CII1DIIEE1EEED0Ev
	.weak	_ZTV1BII1CII1DIIEE1EEES2_S3_EE
	.section	.rodata._ZTV1BII1CII1DIIEE1EEES2_S3_EE,"aG",@progbits,_ZTV1BII1CII1DIIEE1EEES2_S3_EE,comdat
	.align 32
	.type	_ZTV1BII1CII1DIIEE1EEES2_S3_EE, @object
	.size	_ZTV1BII1CII1DIIEE1EEES2_S3_EE, 32
_ZTV1BII1CII1DIIEE1EEES2_S3_EE:
	.quad	0
	.quad	_ZTI1BII1CII1DIIEE1EEES2_S3_EE
	.quad	_ZN1BII1CII1DIIEE1EEES2_S3_EED1Ev
	.quad	_ZN1BII1CII1DIIEE1EEES2_S3_EED0Ev
	.weak	_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.section	.rodata._ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,"aG",@progbits,_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,comdat
	.align 32
	.type	_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, @object
	.size	_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, 32
_ZTV1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE:
	.quad	0
	.quad	_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.quad	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED1Ev
	.quad	_ZN1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EED0Ev
	.weak	_ZTS1E
	.section	.rodata._ZTS1E,"aG",@progbits,_ZTS1E,comdat
	.type	_ZTS1E, @object
	.size	_ZTS1E, 3
_ZTS1E:
	.string	"1E"
	.weak	_ZTI1E
	.section	.rodata._ZTI1E,"aG",@progbits,_ZTI1E,comdat
	.align 32
	.type	_ZTI1E, @object
	.size	_ZTI1E, 56
_ZTI1E:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTS1E
	.long	0
	.long	2
	.quad	_ZTI1CII1DIIEE1EEE
	.quad	2
	.quad	_ZTI1DIIEE
	.quad	2050
	.weak	_ZTS1DIIEE
	.section	.rodata._ZTS1DIIEE,"aG",@progbits,_ZTS1DIIEE,comdat
	.type	_ZTS1DIIEE, @object
	.size	_ZTS1DIIEE, 7
_ZTS1DIIEE:
	.string	"1DIIEE"
	.weak	_ZTI1DIIEE
	.section	.rodata._ZTI1DIIEE,"aG",@progbits,_ZTI1DIIEE,comdat
	.align 16
	.type	_ZTI1DIIEE, @object
	.size	_ZTI1DIIEE, 24
_ZTI1DIIEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1DIIEE
	.quad	_ZTI1BII1DIIEEEE
	.weak	_ZTS1BII1DIIEEEE
	.section	.rodata._ZTS1BII1DIIEEEE,"aG",@progbits,_ZTS1BII1DIIEEEE,comdat
	.type	_ZTS1BII1DIIEEEE, @object
	.size	_ZTS1BII1DIIEEEE, 13
_ZTS1BII1DIIEEEE:
	.string	"1BII1DIIEEEE"
	.weak	_ZTI1BII1DIIEEEE
	.section	.rodata._ZTI1BII1DIIEEEE,"aG",@progbits,_ZTI1BII1DIIEEEE,comdat
	.align 16
	.type	_ZTI1BII1DIIEEEE, @object
	.size	_ZTI1BII1DIIEEEE, 24
_ZTI1BII1DIIEEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1BII1DIIEEEE
	.quad	_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.weak	_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.section	.rodata._ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE,"aG",@progbits,_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE,comdat
	.align 32
	.type	_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE, @object
	.size	_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE, 36
_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE:
	.string	"1AI12dispatch_fooI1BII1DIIEEEES3_EE"
	.weak	_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.section	.rodata._ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE,"aG",@progbits,_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE,comdat
	.align 16
	.type	_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE, @object
	.size	_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE, 16
_ZTI1AI12dispatch_fooI1BII1DIIEEEES3_EE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1AI12dispatch_fooI1BII1DIIEEEES3_EE
	.weak	_ZTS1CII1DIIEE1EEE
	.section	.rodata._ZTS1CII1DIIEE1EEE,"aG",@progbits,_ZTS1CII1DIIEE1EEE,comdat
	.type	_ZTS1CII1DIIEE1EEE, @object
	.size	_ZTS1CII1DIIEE1EEE, 15
_ZTS1CII1DIIEE1EEE:
	.string	"1CII1DIIEE1EEE"
	.weak	_ZTI1CII1DIIEE1EEE
	.section	.rodata._ZTI1CII1DIIEE1EEE,"aG",@progbits,_ZTI1CII1DIIEE1EEE,comdat
	.align 16
	.type	_ZTI1CII1DIIEE1EEE, @object
	.size	_ZTI1CII1DIIEE1EEE, 24
_ZTI1CII1DIIEE1EEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1CII1DIIEE1EEE
	.quad	_ZTI1BII1CII1DIIEE1EEES2_S3_EE
	.weak	_ZTS1BII1CII1DIIEE1EEES2_S3_EE
	.section	.rodata._ZTS1BII1CII1DIIEE1EEES2_S3_EE,"aG",@progbits,_ZTS1BII1CII1DIIEE1EEES2_S3_EE,comdat
	.align 16
	.type	_ZTS1BII1CII1DIIEE1EEES2_S3_EE, @object
	.size	_ZTS1BII1CII1DIIEE1EEES2_S3_EE, 27
_ZTS1BII1CII1DIIEE1EEES2_S3_EE:
	.string	"1BII1CII1DIIEE1EEES2_S3_EE"
	.weak	_ZTI1BII1CII1DIIEE1EEES2_S3_EE
	.section	.rodata._ZTI1BII1CII1DIIEE1EEES2_S3_EE,"aG",@progbits,_ZTI1BII1CII1DIIEE1EEES2_S3_EE,comdat
	.align 16
	.type	_ZTI1BII1CII1DIIEE1EEES2_S3_EE, @object
	.size	_ZTI1BII1CII1DIIEE1EEES2_S3_EE, 24
_ZTI1BII1CII1DIIEE1EEES2_S3_EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1BII1CII1DIIEE1EEES2_S3_EE
	.quad	_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.weak	_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.section	.rodata._ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,"aG",@progbits,_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,comdat
	.align 32
	.type	_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, @object
	.size	_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, 56
_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE:
	.string	"1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE"
	.weak	_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.section	.rodata._ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,"aG",@progbits,_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE,comdat
	.align 16
	.type	_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, @object
	.size	_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE, 16
_ZTI1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1AI12dispatch_fooI1BII1CII1DIIEE1EEES4_S5_EES6_S4_S5_EE
	.section	.text._ZN1ED2Ev,"axG",@progbits,_ZN1ED5Ev,comdat
	.align 2
	.weak	_ZN1ED2Ev
	.type	_ZN1ED2Ev, @function
_ZN1ED2Ev:
.LFB70:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$_ZTV1E+16, (%rax)
	movq	-8(%rbp), %rax
	movq	$_ZTV1E+48, 8(%rax)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZN1DIIEED2Ev
.L104:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1CII1DIIEE1EEED2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L107
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
.L107:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE70:
	.size	_ZN1ED2Ev, .-_ZN1ED2Ev
	.weak	_ZN1ED1Ev
	.set	_ZN1ED1Ev,_ZN1ED2Ev
	.set	.LTHUNK0,_ZN1ED1Ev
	.section	.text._ZN1ED1Ev,"axG",@progbits,_ZN1ED5Ev,comdat
	.weak	_ZThn8_N1ED1Ev
	.type	_ZThn8_N1ED1Ev, @function
_ZThn8_N1ED1Ev:
.LFB73:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	addq	$-8, %rdi
	jmp	.LTHUNK0
	.cfi_endproc
.LFE73:
	.size	_ZThn8_N1ED1Ev, .-_ZThn8_N1ED1Ev
	.section	.text._ZN1ED0Ev,"axG",@progbits,_ZN1ED5Ev,comdat
	.weak	_ZThn8_N1ED0Ev
	.type	_ZThn8_N1ED0Ev, @function
_ZThn8_N1ED0Ev:
.LFB74:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	addq	$-8, %rdi
	jmp	.LTHUNK1
	.cfi_endproc
.LFE74:
	.size	_ZThn8_N1ED0Ev, .-_ZThn8_N1ED0Ev
	.align 2
	.weak	_ZN1ED0Ev
	.type	_ZN1ED0Ev, @function
_ZN1ED0Ev:
.LFB72:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1ED1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE72:
	.size	_ZN1ED0Ev, .-_ZN1ED0Ev
	.set	.LTHUNK1,_ZN1ED0Ev
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits
