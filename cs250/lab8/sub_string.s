	.file	"sub_string.c"
	.text
	.p2align 4,,15
	.globl	sub_string
	.type	sub_string, @function
sub_string:
.LFB0:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	%edx, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	%edx, %ebp
	subl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	leal	2(%rbp), %edi
	movl	%esi, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movslq	%edi, %rdi
	call	malloc
	cmpl	%ebx, %r13d
	jl	.L4
	movl	%ebp, %r8d
	movslq	%ebx, %rdi
	xorl	%edx, %edx
	addq	$1, %r8
	addq	%r12, %rdi
	.p2align 4,,10
	.p2align 3
.L3:
	movzbl	(%rdi,%rdx), %ecx
	movb	%cl, (%rax,%rdx)
	addq	$1, %rdx
	cmpq	%r8, %rdx
	jne	.L3
.L4:
	movslq	%ebp, %rbp
	movb	$0, 1(%rax,%rbp)
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	sub_string, .-sub_string
	.ident	"GCC: (Gentoo 4.7.3-r1 p1.3, pie-0.5.5) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
