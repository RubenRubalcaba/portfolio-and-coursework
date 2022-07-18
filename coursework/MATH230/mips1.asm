.data
filewords: .space 5000
newline: .asciiz "\n"
prompt: .asciiz "What is your filename? "
output1: .asciiz "The hash value of:\n"
output2: .asciiz "is: "
cr: .word 0xa
linefeed: .word 0xd
finput:   .ascii ""      # filename for input

.text
addi $t8, $zero, 104729

#print prompt
li $v0, 4
la $a0, prompt
syscall

#store into fin
li $v0, 8
la $a0, finput
li $a1, 100
syscall

la $t7, finput
clean:
lb $a3, 0($t7)
beq $a3, '\0', open
beq $a3, 0xa, save
beq $a3, 0xd, save

increment:
addi $t7, $t7, 1
j clean

save:
sb $zero, 0($t7)
j increment

open:
#open
li $v0, 13
la $a0, finput
li $a1, 0
syscall
move $s0, $v0

#read
li $v0, 14
move $a0, $s0
la $a1, filewords
la $a2, 1024
syscall

#print
li $v0, 4
la $a0, output1
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, filewords
syscall

#close
li $v0, 16
move $a0, $s0
syscall

#exit
exit:
li $v0, 10
syscall