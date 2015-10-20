# This is the implementation for sub_string function in x86 assembly language
#%rdi in_string, %rsi start_index %rdx end_index
.data
buffer:
	.space 100

.globl sub_string
.text

sub_string:

movq	%rdi, %r15 #r15 holds in_string
movq	%rsi, %r14 #r14 holds start index
movq	%rdx, %r13 #r13 holds end index
movq	$0 , %r12   #r12 holds counter

dec		%r14
dec		%r13

#movq	%r15, %rdi
#movq	$0 , %rax
#call 	printf



addq	%r14, %r15 #r15 points to the start index of the string
subq	%r14, %r13 #r13 holds end - start
movq	$buffer, %r11

#movq	%r15, %rdi
#movq	$0, %rax
#call	printf
#ret

#movq	%r13, %rdi
#movq	$0, %rax
#call	printf

loop:

movb	(%r15), %al
movb 	%al, (%r11) # r11 is the out_string
inc		%r12
inc		%r15
inc		%r11
cmpq	%r12, %r13
je		end
jmp		loop


end:

movq	$0, (%r11)
subq	%r13, %r11


movq	%r11, %rax
ret


