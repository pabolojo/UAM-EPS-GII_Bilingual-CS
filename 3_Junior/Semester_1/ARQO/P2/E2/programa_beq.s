# Prog de prueba para Pr�ctica 2. Ej 1

.data 0
num0: .word 1 # posic 0
num1: .word 2 # posic 4
num2: .word 4 # posic 8 
num3: .word 8 # posic 12 
num4: .word 16 # posic 16 
num5: .word 32 # posic 20
num6: .word 0 # posic 24
num7: .word 0 # posic 28
num8: .word 0 # posic 32
num9: .word 0 # posic 36
num10: .word 0 # posic 40
num11: .word 0 # posic 44
.text 0
main:
  # carga num0 a num5 en los registros 9 a 14
  lw $t1, 0($zero) # lw $r9, 0($r0)
  lw $t2, 4($zero) # lw $r10, 4($r0)
  lw $t3, 8($zero) # lw $r11, 8($r0)
  lw $t4, 12($zero) # lw $r12, 12($r0)
  lw $t5, 16($zero) # lw $r13, 16($r0)
  lw $t6, 20($zero) # lw $r14, 20($r0)

  add $t4, $t2, $t2 # 2 + 2 = 4
  beq $t4, $t3, efective1 #Efective

  add $t5, $t3, $t1 #Not executed

  efective1:
  add $t4, $t2, $t1 # 2 + 1 = 3
  beq $t4, $t3, efective1 # Not efective

  lw $t4, 4($zero) #Load 2
  beq $t4, $t2, efective2 #Efective

  add $t5, $t4, $t1 #Not executed

  efective2:
  lw $t4, 8($zero) #Load 4
  beq $t4, $t2, efective2 #Not efective