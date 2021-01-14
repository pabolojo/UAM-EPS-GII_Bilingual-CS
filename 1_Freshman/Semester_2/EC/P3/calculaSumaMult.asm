######################################################################
## File: calculaSumaMult.asm
## Description: Progam which calculates the sum of two operators, then
## multiply by 2, everything with a function
## Date:

## Authors: 
## Subject: E.C. 1º grado
## Laboratory group:
## Theory group:
## Task: 3
## Exercise: 1
######################################################################

.text

main:		
	#Reading of X variable and save it in a register
	lw $s0,X
	#Reading of Y variable and save it in a register
	lw $s1,Y
	#PUSH of register equivalent to X
	addi $sp,$sp,-4
	sw $s0,0($sp)
	#PUSH of register equivalent to Y
	addi $sp,$sp,-4
	sw $s1,0($sp)
	#Function call
	jal calculaSumaMult
	#Recovery of return with a POP
	lw $s2,0($sp)
	addi $sp,$sp,4
	#Saving the return in the R variable of memory
	sw $s2,R
	#Infinitive loop
	end:
	j end
calculaSumaMult:
	#Recovery of the second parameter with a POP
	lw $t0,0($sp)
	addi $sp,$sp,4
	#Recovery of the first parameter with a POP
	lw $t1,0($sp)
	addi $sp,$sp,4
	#Suma of two parameters
	add $t0,$t0,$t1
	#Multiply by two
	sll $t0,$t0,1
	#PUSH of result 
	addi $sp,$sp,-4
	sw $t0,0($sp)
	#Return to main
	jr $ra
	
	

.data
X: 10
Y: 4
R:
