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

                MOV AX , 13H        ;Load 13H in AX
                MOV BX , 0BAH       ;Load BAH in BX
                MOV CX , 3412H      ;Load 3412H in CX
                MOV DX , CX         ;Load the content of CX in DX
                MOV AX , 6000H
                MOV DS , AX
                MOV AX , DS:[5246H] ;Load [65246H] in AL and [65247H] in AH
                MOV AX , 4000H
                MOV DS , AX
                MOV DS:[4H] , CH    ;Load CH in [40004H]
                MOV AX , 0H
                MOV DS , AX
                MOV AX , [DI]       ;Load 0000:[DI] in AX
                MOV AX , DS:BP[8H]  ;Load 0000:[BP] + 8 in AX

            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP
; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO


