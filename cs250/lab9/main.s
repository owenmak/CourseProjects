.data

start_ind:
	.quad 0
end_ind:
	.quad 0
str:
	.space 100

.text
.prompt1:
	.string "Enter a string: "
.prompt2:
	.string "Enter the start index: "
.prompt3:
	.string "Enter the end index: "
.prompt4:
	.string "The substring of the given string is '%s'\n";
.scan1:
	.string "%d"
.scan2:
	.string "%s"

.globl main

main:
	
	movq	$.prompt1,%rdi
	movq	$0, %rax
	call	printf

	movq	$.scan2, %rdi
	movq	$str, %rsi
	movq	$0, %rax
	call	scanf
	
	movq	$.prompt2, %rdi
	movq	$0, %rax
	call	printf

	movq	$.scan1, %rdi
	movq	$start_ind, %rsi
	movq	$0, %rax
	call	scanf

	movq	$.prompt3, %rdi
	movq	$0, %rax
	call	printf

	movq	$.scan1, %rdi
	movq	$end_ind, %rsi
	movq	$0, %rax
	call	scanf

#	movq	$str, %rdi
#	movq	$0, %rax
#	call	printf

	movq	$start_ind, %r15
	movq	$end_ind, %r14
	movq	(%r15), %r15
	movq	(%r14), %r14
	
	movq	$str, %rdi
	movq	%r15, %rsi
	movq	%r14, %rdx
	call	sub_string

	movq	$.prompt4, %rdi
	movq	%rax, %rsi
#	movq	(%rsi), %rsi
	movq	$0, %rax
	call	printf

	ret
