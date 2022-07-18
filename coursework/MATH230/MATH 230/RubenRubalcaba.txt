#Ruben Rubalcaba
#Instructor: Professor Mimi 
#November 20, 2019
#Math 230-03


#Graceful exit macro

.macro done
li $v0, 10 
syscall 
.end_macro

#Print string
.macro print_str (%str)
li $v0, 4
la $a0, %str
syscall
.end_macro

.data
prompt1: .asciiz "Enter your first string no spaces (16 total): "
prompt2: .asciiz "Enter your second string no spaces (16 total): "
prompt3: .asciiz "\nEnter an integer between 0 & 15 (to be later used as an upper limit for splitting the arrays): "
prompt4: .asciiz "You entered the following:\n"
newline: .asciiz "\n"
String:  .asciiz "\n\nCreating newly evolved candidates from your specified inputs... \nChild one and two are shown below:\n\n"
Parent:.space 17
Parent2: .space 17
Child: .space 17
Child2: .space 17
.text
main: 
	print_str(prompt1)
	#taking in user input
	li $v0,8
	la $a0,Parent
	li $a1,17
	syscall
	print_str(newline)
	#Display prompt
	print_str(prompt2)
	#taking second input
	li $v0, 8
	la $a0,Parent2
	li $a1, 17
	syscall
	print_str(prompt3)
	#taking user input for split
	li $v0, 5
	syscall
	
	#Move scanned int into temporary register
	move $t0, $v0
	
	print_str(newline)
	print_str(prompt4)
	
	#Print each taken output
	print_str(Parent)
	print_str(newline)
	print_str(Parent2)
	print_str(newline)
	#print scanned int
	li $v0, 1
	move $a0, $t0
	syscall
	print_str(String)
	
	#Create counter variable
	add $t1,$t1,$zero
	
	#Load each string into a register
	la $t2, Parent
	la $t3, Parent2
	la $t4, Child
	la $t5, Child2

Loop: 
	#Branch if indez is equal to length 
	beq $t1, 16, Exit
	#Load values of parents into 2 register and insert into children
	
	lb $s2,($t2)
	lb $s3,($t3)
	
	#Branch if index is greater than chosen int
	
	bgt $t1,$t0, Crossover
	
	sb $s2,($t4)
	sb $s3,($t5)
	
	#Fall through into increment
Increment:
	#Move to next index of strings
	addi $t1, $t1, 1
	addi $t2, $t2, 1  
	addi $t3, $t3, 1
	addi $t4, $t4, 1
	addi $t5, $t5, 1
	j Loop 
	
Crossover:
	#Swap values of strings
	sb $s2, ($t5)
	sb $s3, ($t4)
	#Jump back to Increment Loop
	j Increment
	
Exit:
	#Print children strings
	print_str(Child)
	print_str(newline)
	print_str(Child2)
	print_str(newline)
	done