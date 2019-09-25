# --------------------------------------------------------
# Subject	: CST337 - Computer Architecture
#                 Dr. Eckhardt
# Homework	: 2
# Student	: Clarence Mitchell
# DateDue	: 7-19-2016
# FileName	: PrimeNumbers.asm
#--------------------------------------------------------
	#------------------------------------------------
	#
	# DATA STORAGE 
	#
	#-----------------------------------------------
	.data 
	begstr: .ascii "\n--- Start of Program ---\n\n" 
		.ascii "Prime numbers from 1 to 100:\n"
		.asciiz "1, 2"
	endstr:	.asciiz "\n\n--End of Program.\n"
	endln:	.asciiz "\n"
	blank:	.asciiz " "
	comma: 	.ascii ", "
	.text 
	#------------------------------------------------
	#
	# START OF CODE 
	#
	#-----------------------------------------------
	# print Start of program message
		li	$v0, 4							        # service 4 is print string
		la	$a0, begstr
		syscall 
	#
	#  Initialize $t1 - start number and $t2 - end number
	#
		addi	$t1,$zero,3
		addi	$t2,$zero,101

	Mainloop:
		jal	CheckPrime						        # check if prime (returns $T0 0 - no prime, 1 - prime )
		beqz    $t0, IncrNum						        # Not Prime so contine with increment and mainloop
		jal	PrintPrime
	#
	# increment loop counter and check for end value 
	#
	IncrNum:   	
			addi	$t1,$t1,1
			bne 	$t1,$t2,Mainloop
		b 	EndPgm

	 #-------------------------------------------
	 # CheckPrime Routine
	 #-----------------------------------------
	 # Routine to check for Prime Number in $t1 
	 #
	 # Uses $t4, $t5, $t6 and $t7
	 #   $t4 loop counter from 2 to $t1 - 1 value
	 #   $t5 is value of division 
	 #   $t6 is remainder 
	 # Sets $t0 to 
	 #	0 if not prime
	 #	1 if prime
	 #
	 CheckPrime:
		
		addi	$t0, $zero,0						      # Initailize $t0 to 0 (non prime)
		addi	$t4, $zero,2						      # Initailize $t4 to 2

	CheckLoop:
		div 	$t5, $t1, $t4						      # set $t5 = $t1 / $t4
		mfhi 	$t6							      # set $t6 to remainder
		beq		$t6, $zero, ExitPrimeCheck			      # No remainder so exit
		addi	$t4, $t4 1						      # Add 1 to $t4
		beq	$t4,$t1, FoundPrime					      # Have searched all values from 2 to n 
		b  	CheckLoop						      # return to checkloop
	 FoundPrime:
		addi	$t0, $t0, 1						      # Set $t0 to 1 (prime)
	 ExitPrimeCheck:
		jr	$ra
	 #-------------------------------------------
	 # PrintPrime Routine
	 #-----------------------------------------
	 #
	 # Routine to print Prime Number 
	 #  then return to Mainloop (via save progam counter)
	 #
	PrintPrime:
		#
		# Print comma then prime number
		li	$v0, 4							      # Set service to print string
		la	$a0, comma						      # load address of comma string
		syscall 							      # call system print
		#
		# Now print number
		#
		li	$v0, 1							      # Set Service to print number
		add 	$a0, $t1, $zero					              # load value in temp 1
		syscall 
		jr 	$ra							      # Return to  mainloop
	 
	#======================================
	##
	## End of program
	##
	#=======================================	
	EndPgm:   	
	# print end of program message
		li	$v0, 4							     # service 4 is print string
		la	$a0, endstr
		syscall 
	 #
		li	$v0, 10
		syscall 
