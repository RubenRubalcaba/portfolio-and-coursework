#Ruben Rubalcaba 
#Instructor: Professor Mimi Rasky 
#Math 230-03 
#Lab #9

#Graceful exit
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
	buffer: .space 5000
	prompt1: .asciiz "What is your filename? "
	prompt2: .asciiz "The hash value of:\n "
	prmopt3: .asciiz "is: "
	cr: .word 0xa
	linefeed: .word 0xd
	filename: .asciiz " "
	newline: .asciiz "\n"
.text
	addi $t8, $zero, 104729
	add $t9, $t9, '\0'
	print_str(prompt1)
	#taking in user FILW
	li $v0,8
	la $a0,filename
	li $a1,100
	syscall
	
	
	la $t7, filename
	CLEAN:
	#lb and go through filename and clean and store word jump back to clean and clean string of new line
	beq $t7, $t9, EXIT
	
	
	j CLEAN
	
	OPEN:
	li   $v0, 13       # system call for open file
	la   $a0, filename      # board file name
	li   $a1, 0        # Open for reading
	li   $a2, 0
	syscall            # open a file (file descriptor returned in $v0)
	move $s6, $v0      # save the file descriptor
	
	#read from file
	li   $v0, 14       # system call for read from file
	move $a0, $s6      # file descriptor 
	la   $a1, buffer   # address of buffer to which to read
	li   $a2, 1024     # hardcoded buffer length
	syscall            # read from file 
	
	li   $v0, 16       # system call for close file
	move $a0, $s6      # file descriptor to close
	syscall            # close file
	
	HASH:
	#mult
	mflo $t4
	#div 
	mfhi $t6
	EXIT:
	#print end string here
	
	done