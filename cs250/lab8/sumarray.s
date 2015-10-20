.data

.section .bss
	.lcomm number, 32

.text
.prompt1:
	.string "Please insert five numbers:\n "
.prompt2:
	.string "The sum is: %d\n"
.scan:
	.string "%d"

.globl main

main:
	
	movq	$.prompt1,%rdi
	movq	$0, %rax
	call	printf
	movq	$0, %r15 #Counter
	movq	$0, %r14 #sum

loop:
	movq	$.scan, %rdi
	movq	$number, %rsi
	movq	$0, %rax
	call	scanf


	movq	$number, %rbx
	addq	%rbx, %r14
	addq	$1, %r15
	cmpq	$5, %r15
	je		end
	jmp		loop

end:
	movq	$.prompt2, %rdi
	movq	%r14, %rsi
	movq	(%rsi), %rsi
	movq	$0, %rax
	call	printf
	ret
