# ---------------------------------------------
# Subject	: CST337 - 
# Homework	: 2
# Student	: Clarence Mitchell
# DateDue	: 7-19-2016
# FileName	: PrimeNumbers.asm
#--------------------------------------------
	.data 
begstr: .ascii "\n--- Start of Program ---\n\n" 
	.ascii "Prime numbers from 1 to 100:\n"
	.asciiz "1, 2"
endstr:	.asciiz "\n\n--End of Program.\n"
endln:	.asciiz "\n"
blank:	.asciiz " "
comma: .ascii ", "
numout:	.word	
	.text 
ori $t1, $zero, 34

add $t2, $t1, $zero

mult $t1, $t1

mflo $t3

ori $t4, $zero, 3

mult $t2, $t4

mflo $t5

add $t1, $t3, $t5
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
 #
 	li	$v0, 10
 	syscall 