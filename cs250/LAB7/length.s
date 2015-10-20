.text


main:
la $a0, prompt1
li $v0, 4
syscall

li $t1, 0

li $v0, 8
la $a0, buffer
li $a1, 50
move $t0,$a0
syscall

loop:
lb $t2, 0($t0)
beqz $t2, end
add $t1, $t1, 1 #t1 is the counter
add $t0, $t0, 1
j loop


end:
sub $t1, $t1, 1

li $v0, 4
la $a0, prompt2
syscall

li $v0, 1
move $a0, $t1
syscall

li $v0, 10
syscall

.data
prompt1: .asciiz "Enter a string(50 max): "
prompt2: .asciiz "The length of the string is: "
buffer: .space 50
