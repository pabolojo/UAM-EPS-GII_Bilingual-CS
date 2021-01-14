;**************************************************************************
; MBS 2020. LAB 4
;
; p4b_mem.asm  Memory input
;
; Team Number XX:
;**************************************************************************

; DATA SEGMENT DEFINITION
DATOS SEGMENT
    DECI DB "456$"          ;0x1C8 in hexadecimal
    HEX DB "ABC$"           ;2748 in decimal

    RESULT DB 7 dup (?)     ; Buffer for the result

    ; Strings for user info
    PRINT1 DB "The number $"
    PRINT11 DB "The number 0x$"
    PRINT2 DB " in decimal is: $"
    PRINT3 DB " in hexadecimal is: 0x$"
    PRINT4 DB 13, 10, '$'
DATOS ENDS
;**************************************************************************

; STACK SEGMENT DEFINITION
PILA SEGMENT STACK "STACK"
    DB 40H DUP (0)
PILA ENDS
;**************************************************************************

; CODE SEGMENT DEFINITION
CODE SEGMENT
    ASSUME CS: CODE, DS: DATOS, SS: PILA ; We assign the default registers of the data in the segments
    ; BEGINNING OF THE MAIN PROCEDURE
    INICIO PROC
        ; INITIALIZE THE SEGMENT REGISTERS
        MOV AX, DATOS
        MOV DS, AX
        MOV AX, PILA
        MOV SS, AX
        MOV SP, 64 ; LOAD THE STACK POINTER WITH THE HIGHEST VALUE

            ; PROGRAM START

                ; This is only a set of print options that show the results of the 55h interruption
                MOV AH, 9                       ; We load the print option

                MOV DX, OFFSET PRINT1           ; We set the message to print
                INT 21H                         ; We call the interrupt to print

                MOV CX, OFFSET DECI             ; We set the message to print
                MOV DX, CX
                INT 21H                         ; We call the interrupt to print

                MOV DX, OFFSET PRINT3
                INT 21H                         ; We call the interrupt to print


                ; HERE WE CALL THE INTERRUPTION
                MOV AH, 10h                     ; We set the HEX (10H) option
                MOV DX, OFFSET RESULT           ; We set the result buffer
                INT 55H                         ; And we call the interruption


                MOV AH, 9                       ; We load the print option
                MOV DX, OFFSET RESULT
                INT 21H                         ; We call the interrupt to print
                
                MOV DX, OFFSET PRINT4
                INT 21H                         ; We call the interrupt to print


                MOV DX, OFFSET PRINT11           ; We set the message to print
                INT 21H                         ; We call the interrupt to print

                MOV CX, OFFSET HEX
                MOV DX, CX
                INT 21H                         ; We call the interrupt to print

                MOV DX, OFFSET PRINT2
                INT 21H                         ; We call the interrupt to print


                ; HERE WE CALL THE INTERRUPTION
                MOV AH, 11h                     ; We set the HEX (10H) option
                MOV DX, OFFSET RESULT           ; We set the result buffer
                INT 55H                         ; And we call the interruption


                MOV AH, 9
                MOV DX, OFFSET RESULT
                INT 21H                         ; We call the interrupt to print

                MOV DX, OFFSET PRINT4
                INT 21H                         ; We call the interrupt to print

            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP

; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO


