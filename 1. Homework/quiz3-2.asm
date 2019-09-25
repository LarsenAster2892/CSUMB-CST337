

main:
addi $t0,$zero, 0
addi $t1,$zero, 0
addi $t2,$zero, 5
repeat:
addi $t1,$t1, 1
jal procedure 
bne $t1,$t2, repeat
exit:	
	 #
		li	$v0, 10
		syscall 
procedure:
addi $t0,$t0, 2
jr $ra
