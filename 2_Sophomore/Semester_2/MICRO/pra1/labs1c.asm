;**************************************************************************
; MBS 2020. LAB 1
;
; Team Number XX:
;**************************************************************************

; DATA SEGMENT DEFINITION
DATOS SEGMENT

DATOS ENDS
;**************************************************************************

; STACK SEGMENT DEFINITION
PILA SEGMENT STACK "STACK"
    DB 40H DUP (0) ; initialization example, 64 bytes set to 0
PILA ENDS
;**************************************************************************

; EXTRA SEGMENT DEFINITION
EXTRA SEGMENT
    RESULT DW 0,0 ; initialization example. 2 WORDS (4 BYTES)
EXTRA ENDS
;**************************************************************************

; CODE SEGMENT DEFINITION
CODE SEGMENT
    ASSUME CS: CODE, DS: DATOS, ES: EXTRA, SS: PILA ; We assign the default registers of the data in the segments
    ; BEGINNING OF THE MAIN PROCEDURE
    INICIO PROC
        ; INITIALIZE THE SEGMENT REGISTERS
        MOV AX, DATOS
        MOV DS, AX
        MOV AX, PILA
        MOV SS, AX
        MOV AX, EXTRA
        MOV ES, AX
        MOV SP, 64 ; LOAD THE STACK POINTER WITH THE HIGHEST VALUE

            ; PROGRAM START

			;We initialize the values
			;First the segments
			MOV AX, 0333H
			MOV ES, AX
			MOV AX, 0511H
			MOV DS, AX
			;And then the registers
			MOV BX, 0211H
			MOV DI, 1010H


			;Now we execute the code and check in the TD that the values that we have stored in
			;the calculated real addresses match with the ones retrived
			;by the following instructions. And indeed, they do.
			MOV AL, DS:[1234H]   ;05110H + 1234H = 06344H
			MOV AX, [BX]		     ;05110H + 0211H = 05321H
			MOV [DI], AL		     ;05110H + 1010H = 06120H

			;We assume ES = 0333H
			MOV AL, ES:[3014H]	  ;06344H - 03330H = 3014H
			MOV SI, 1FF1H
			MOV AX, ES:[SI]		    ;05321H - 03330H = 1FF1H
			MOV ES:[2DF0H], AL	  ;06120H - 03330H = 2DF0H


            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP
; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO


