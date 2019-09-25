# ---------------------------------------------
# Subject	: CST337 - 
# Assignment	: 1
# Student	: Clarence Mitchell
# DateDue	: 7-19-2016
# FileName	: xxx.asm
#--------------------------------------------
	.data 
begstr: .ascii "\n--- Start of Program ---\n" 
	.ascii "Prime numbers from 1 to 100:\n"
	.asciiz "1, 2"
endstr:	.asciiz "\n--End of Program.\n"
endln:	.asciiz "\n"
blank:	.asciiz " "
comma: .ascii ", "
numout:	.word
	.asciiz ""	
	.text 
# print Start of program message
	li	$v0, 4		# service 4 is print string
	la	$a0, begstr
	syscall 
	
	
	addi	$t1,$zero,3
	addi	$t2,$zero,101

Mainloop:
#	li  	$v0, 1           # service 1 is print integer
#    	add 	$a0, $t1, $zero  # load desired value into argument register $a0, using pseudo-op
#    	syscall
# print space
#	sw	$t1,numout
#	li	$v0, 4		# service 4 is print string
#	la	$a0,output
#	syscall 
	jal	CheckPrime		# check if prime (returns $T0 0 - no prime, 1 - prime )
	beqz    $t0, IncrNum		# Not Prime so contine with increment and mainloop
	jal	PrintPrime
# increment loop counter and check for end value 
IncrNum:   	
    	addi	$t1,$t1,1
    	bne 	$t1,$t2,Mainloop
 	j	EndPgm

 #
 # Routine to check for Prime Number in $t1 
 # Uses $t4, $t5, $t6 and $t7
 #   $t4 loop counter from 2 to $t1 - 1 value
 #   $t5 is value of division 
 #   $t6 is remainder 
 # Sets $t0 to 
 #	0 if not prime
 #	1 if prime
 #
 CheckPrime:
 	
 	addi	$t0, $zero,0			# Initailize $t0 to 0 (non prime)
 	addi	$t4, $zero,2			# Initailize $t4 to 2

CheckLoop:
 	div 	$t5, $t1, $t4			# set $t5 = $t1 / $t4
 	mfhi 	$t6				# set $t6 to remainder
 	beq	$t6, $zero, ExitPrimeCheck	# No remainder so exit
 	addi	$t4, $t4 1			# Add 1 to $t4
 	beq	$t4, $t1, FoundPrime		# Have searched all values from 2 to n 
 	j 	CheckLoop			# return to checkloop
 FoundPrime:
 	addi	$t0, $t0, 1			# Set $t0 to 1 (prime)
 ExitPrimeCheck:
 	jr	$ra
 #
 # Routine to print Prime Number then return to Mainloop
 #
PrintPrime:
	#
	# Print comma then prime number
	li	$v0, 4			# Set service to print string
 	la	$a0, comma		# load address of comma string
 	syscall 			# call system print
 	#
 	# Now print number
 	li	$v0, 1			# Set Service to print number
 	add 	$a0, $t1, $zero		# load value in temp 1
 	syscall 
 	jr 	$ra		# Return to  mainloop
 
#======================================
##
## End of program
##
#=======================================	
EndPgm:   	
# print end of program message
	li	$v0, 4		# service 4 is print string
	la	$a0, endstr
	syscall 
    	