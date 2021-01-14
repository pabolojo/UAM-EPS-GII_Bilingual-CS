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
	add $s1, $s0, $s0
	add $s0, $s1,$s1
 
	#Initialization the for loop
	addi $t0, $0, 0
	
	
	#Checking the loop
	for: beq $t0, $s0, bucle	
	
	#Reading of A(i)
	lw $t2, A($t0)
	
	#Reading of B(i)
	lw $t1, B($t0)
	
	#Multiplication by 4 of B(i)
	add $t4, $t1, $t1
	add $t1, $t4,$t4
	
	#Addition 
	add $t3, $t1, $t2
	
	#Writing in C(i)
	sw $t3, C($t0)
	
	#Loop opeartion
	addi $t0, $t0,4
	
	#Jump to the comparison
	j for
	
	#Infinitive loop
	
	bucle: j bucle
.data # Start of user memory data
N: .word 6
A: 2,4,6,8,10,12
B: -1,-5,4,10,1,-5
C: 