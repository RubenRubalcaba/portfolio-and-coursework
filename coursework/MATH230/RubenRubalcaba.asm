#Ruben Rubalcaba 
#Instructor: Professor Mimi Rasky 
#Math 230-03 
#Lab #9
#December 3, 2019

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
	prompt2: .asciiz "The hash value of:\n"
	prompt3: .asciiz "\nis: "
	filename: .asciiz ""
.text
	addi $t0,$t0, 31
	add $t2,$t2, $zero
	addi $t8, $zero, 104729
	
	print_str(prompt1)
	#taking in user FILE
	li $v0,8
	la $a0,filename
	li $a1,100
	syscall
	
	#Load filename into t7
	la $t7, filename
	
	#clean function if byte is equal to linefeed clean byte
	CLEAN: 
		lb $a3,0($t7)
		beq $a3, '\0', OPEN
		beq $a3, 0xa, CONT
		beq $a3, 0xd, CONT
	
	INCREMENT:
		addi $t7, $t7, 1
		j CLEAN
	CONT:
		sb $zero, 0($t7)  #Store ascii null into byte place
		j INCREMENT 
	
	
	OPEN:
		li   $v0, 13       # system call for open file
		la   $a0, filename      # board file name
		li   $a1, 0        # Open for reading
		syscall            # open a file (file descriptor returned in $v0)
		move $s0, $v0      # save the file descriptor
	
		#read from file
		li   $v0, 14       # system call for read from file
		move $a0, $s0      # file descriptor 
		la   $a1, buffer   # address of buffer to which to read
		li   $a2, 1024     # hardcoded buffer length
		syscall            # read from file
	
		li   $v0, 16       # system call for close file
		move $a0, $s0      # file descriptor to close
		syscall            # close file 
	
	la $t4, buffer	#Load buffer into t4 register 
	HASH:
		lb $t6, 0($t4)
		beq $t6, '\0', EXIT
		beq $t6, 0xd,IGNORE	#ignore carriage return 
		mult $t0, $t2	#31*h
		mflo $t9  #t9 = 31*h
		add $s6, $t9, $t6   #31*h + $t6
		div $s6, $t8 
		mfhi $t2	#h = (31*h + v) % 104729
		j NEXTPLACE 
	
	IGNORE:
		addi $t4, $t4,1 #iterate next place
	
	NEXTPLACE:
		addi $t4, $t4,1 #iterate next place
		j HASH
	
	EXIT:
		print_str(prompt2)
		print_str(buffer)
		print_str(prompt3)
		
		li $v0,1     #prepare system call
		add $a0,$zero,$t2 #copy t2 to a0
		syscall      #print integer
		
		done
	
	
