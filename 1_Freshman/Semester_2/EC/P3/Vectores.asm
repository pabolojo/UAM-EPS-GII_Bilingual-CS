######################################################################
## File: Vectores.asm
## Description: Program to...
## Date: 

## Authors: 
## Subject: E.C. 1º grado
## Laboratory group:
## Theory group
## Task: 3
## Exercise: 2
######################################################################

.text

main:		
	#Reading N variable
	lw $s0,N
	
	#Adaptation of N
	sll $s0,$s0,2
	
	#Initialization the for loop
	andi $s1,$s1,0
	
	#Checking the loop
	loop:
	slt $t0,$s1,$s0
	beq $t0,$zero,end
	#Reading of A(i)
	lw $t1,A($s1)
	
	#Reading of B(i)
	lw $t2,B($s1)
	
	#Multiplication by 4 of B(i)
	sll $t2,$t2,2
	
	#Addition 
	add $t1,$t1,$t2
	
	#Writing in C(i)
	sw $t1,C($s1)
	
	#Loop opeartion
	addi $s1,$s1,4
	
	#Jump to the comparison
	j loop
	
	#Infinitive loop
	end: j end

.data # Start of user memory data
A: 2,2,4,6,5,6,7,8,9,10
B: -1,-5,4,10,1,-2,5,10,-10,0
C: .space 40 #.space reserve space in bytes.
N: .word 10

