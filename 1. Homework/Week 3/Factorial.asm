# --------------------------------------------------------
# Subject	: CST337 - Computer Architecture
# Instrutor     : Dr. Eckhardt
# Homework	: 3
# Description   : Calculates Factorial 
# Student	: Clarence Mitchell
# DateDue	: 7-26-2016
# FileName	: Factorial.asm
#--------------------------------------------------------
	#------------------------------------------------
	#
	# DATA STORAGE 
	#
	#-----------------------------------------------
	.data 
		begstr: .ascii "\n--- Start of Program ---\n\n" 
			.asciiz "Factorial numbers from 1 to "
		facstr:	.asciiz "Factorial for "
		isstr:	.asciiz " is: "
		endstr:	.asciiz "\n\n--End of Program.\n"
		endln:	.asciiz "\n"
		blank:	.asciiz " "
		colona:	.asciiz ":\n"
	#
	#  Factorial number used
	#
	.align 2
		facNum:	.word 6	
	.text 
	#------------------------------------------------
	#
	# START OF CODE 
	#
	#-----------------------------------------------
	# print Start of program message
		jal	PrintPgmStart
	#
	#  Initialize parameter with constant value 
	#
		lw	$a0,facNum
	#
	#  Main processing
	#
		jal	Factorial						        # Call Factorial routine
		add	$a0, $v0, $zero							# Now store return value into parameter for print routine 
		jal	PrintFactorial							# Call Print routine
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


	 #-------------------------------------------
	 # Factorial Routine
	 #-----------------------------------------
	 # Routine to calculates the factorial 
	 #
	 # Uses
	 #	input:  $a0 - factorial number to calculate 
	 #	output: $v0 - calcluated factorial value
	 #
	 #
	 Factorial:
		#
		#  Push values onto stack for later
		#
		addi	$sp, $sp, -8						      # Adjust stack Pointer 
		sw	$ra, 0($sp)						      # Save return address
		sw	$s0, 4($sp)						      # Save temporary registered used to calculate factorial

		# start of actual procedure work
		add 	$s0, $a0, $zero						      # initial $s0 to parameter value
		addi	$v0, $zero, 1						      # branch does not allow immediate compares so load 1
		beq	$s0, $v0, ExitFactorial					      # if we have reached 1 then exit recursive calls
		addi    $a0, $s0,-1						      # subtract 1 from saved value and pass as parameter to recursive call
		jal	Factorial						      # call Factorial recursively 
		#
		#  Since we did a jump and link, 
		#  We only get here after we have returned from the recursive call
		#
		mult    $v0,$s0							      # multiply temporary saved by what is return
		mflo    $v0							      # return the results of multiply
		#
		#  Pop (restore) from stack and exit call
		# 
	  ExitFactorial:
		lw	$ra, 0($sp)						      # restore return address
		lw	$s0, 4($sp)						      # restore temporary storage
		addi    $sp, $sp, 8						      # Set stack pointer back
		jr	$ra							      # return from call
		
	 #-------------------------------------------
	 # Print Factrorial Number and Resultse
	 #-----------------------------------------
	 #
	 # Routine to print Factorial Number
	 #     and caluclated value 
	 #  
	 #
	PrintFactorial:
		#
		#  Save parameter for print
		#
		add	$t0, $a0, $zero						      # Move parameter to t0
		
		#
		# Print factorial message (beginning part)
		li	$v0, 4							      # Set service to print string
		la	$a0, facstr 						      # load address of facstr string
		syscall 							      # call system print
		
		#
		# Pirnt Factorial Number
		#
		li	$v0, 1							       # Set Service to print number
		lw	$a0, facNum						       # Set Service to print number
		#add 	$a0, $t0, $zero					               # load value from t0 into parameter to print
		syscall 

		#
		# Print facorial message (end part)
		li	$v0, 4							      # Set service to print string
		la	$a0, isstr 						      # load address of comma string
		syscall 							      # call system print		
		
		#
		# Now factorial number
		#
		li	$v0, 1							      # Set Service to print number
		add 	$a0, $t0, $zero					              # load value from t0 into parameter to print
		syscall 
		jr 	$ra							      # Return to  main
	 
	 #-------------------------------------------
	 # Print Program Start Messages
	 #-----------------------------------------
	 #
	 # Routine to print Start of Program Information
	 #  
	 #
	 PrintPgmStart:
		li	$v0, 4							        # service 4 is print string
		la	$a0, begstr
		syscall 
		#
		# End value
		#
		li	$v0, 1							       # Set Service to print number
		lw	$a0, facNum						       # Set Service to print number
		#add 	$a0, $t0, $zero					               # load value from t0 into parameter to print
		syscall 

		#
		# Print number 
		li	$v0, 4							      # Set service to print string
		la	$a0, colona 						      # load address of comma string
		syscall 							      # call system print
	 
		jr 	$ra							      # Return to  main																		
