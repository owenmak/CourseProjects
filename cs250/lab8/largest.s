.data

.section .bss
#	.lcomm number1, 32
#	.lcomm number2, 32
number1:	.quad 0
number2:	.quad 0
.text
.prompt1:
	.string "Please insert a number: "
.prompt2:
	.string "Please insert another number: "
.prompt3:
	.string "The larger one is: %d\n"
.scan:
	.string "%d"

.globl main

main:
	
	movq	$.prompt1,%rdi
	movq	$0, %rax
	call	printf

	movq	$.scan, %rdi
	movq	$number1, %rsi
	movq	$0, %rax
	call	scanf
	
	movq	$.prompt2,%rdi
	movq	$0, %rax
	call	printf

	movq	$.scan, %rdi
	movq	$number2, %rsi
	movq	$0, %rax
	call	scanf


	movq	$number1, %rbx
	movq	$number2, %rcx

	cmpq	%rbx, %rcx
	jg		end
	movq	$.prompt3, %rdi
	movq	%rbx, %rsi
	movq	(%rsi), %rsi
	movq	$0, %rax
	call	printf
	ret

end:
	movq	$.prompt3, %rdi
	movq	%rcx, %rsi
	movq	(%rsi), %rsi
	movq	$0, %rax
	call	printf
	ret
