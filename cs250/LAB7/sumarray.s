.text


main:
li $t0, 5
li $t1, 0
li $t2, 0
loop:
beq $t1, $t0, end
la $a0, prompt1
li $v0, 4
syscall
li $v0, 5
syscall
move $t3, $v0
addu $t2, $t2, $t3
addi $t1, $t1, 1
j loop

end:
la $a0, prompt2
li $v0, 4
syscall
li $v0, 1
move $a0, $t2
syscall

li $v0, 10
syscall

.data
prompt1: .asciiz "Enter a number: "
prompt2: .asciiz "The sum is: "
