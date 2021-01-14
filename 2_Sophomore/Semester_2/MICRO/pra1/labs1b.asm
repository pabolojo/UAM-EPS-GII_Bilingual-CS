;**************************************************************************
; MBS 2020. LAB 1
;
; Team Number XX:
;**************************************************************************

; DATA SEGMENT DEFINITION
DATOS SEGMENT
    ;We initialize the variables that are required
    COUNTER DB ?                            ;COUNTER of 1 byte
    GRAB DW 0CAFEH                          ;GRAB of 2 bytes with value CAFEH
    TABLE100 DB 100 DUP (?)                 ;TABLE100 of 100 bytes
    ERROR1 DB "Incorrect data. Try again$"  ;ERROR1 string initialized

DATOS ENDS
;**************************************************************************

; STACK SEGMENT DEFINITION
PILA SEGMENT STACK "STACK"
    DB 40H DUP (0) ; initialization example, 64 bytes set to 0
PILA ENDS
;**************************************************************************

; EXTRA SEGMENT DEFINITION
EXTRA SEGMENT

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
            
            ;Then we perform the data manipulations that are required
            MOV AH , ERROR1[5]
            MOV TABLE100[53H] , AH          ;6th character of ERROR1 in TABLE[53H]
            MOV AX , GRAB
            MOV WORD PTR TABLE100[23H] , AX ;GRAB just after TABLE100[22H] => 23H
            MOV COUNTER , AH                ;MSB of GRAB in COUNTER

            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP
; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO


