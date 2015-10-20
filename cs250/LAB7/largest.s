.text


main:
la $a0, prompt1
li $v0, 4
syscall

li $v0, 5
syscall
move $t0,$v0

la $a0, prompt2
li $v0, 4
syscall

li $v0, 5
syscall
move $t1,$v0


bge $t0, $t1, result


move $t0, $t1


result:
la $a0, prompt3
li $v0, 4
syscall

li $v0, 1
move $a0, $t0
syscall

li $v0, 10
syscall

.data
prompt1: .asciiz "Enter a number: "
prompt2: .asciiz "Enter another number: "
prompt3: .ascii "The bigger number is: "
