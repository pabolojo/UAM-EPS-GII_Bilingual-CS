;**************************************************************************
; MBS 2020. LAB 2 
;
; Team Number XX:
;**************************************************************************

; We set the external functions that we are going to use
EXTRN Init_WAV_Header : FAR
EXTRN fopen : FAR
EXTRN fclose : FAR
EXTRN Write_WAV : FAR

; DATA SEGMENT DEFINITION
DATOS SEGMENT
    TEXT DB "gen_la.wav", 0                     ; We set the name of the file and the data for the note
    LA DB 445 DUP (9 DUP (50), 9 DUP(-50))      ; 445 * (9 + 9) = 8010 > 8000
    ERROR DW 0,'$'
    ERROR1 DB "Error opening file", 13, 10, '$' ; We set the error messages
    ERROR2 DB "Error writing WAV", 13, 10, '$'
    ERROR3 DB "Error closing file", 13, 10, '$'
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
            MOV DX, 8000            ; We set the sample rate
            MOV CX, 8000            ; We set the number of samples
            CALL Init_WAV_Header    ; We create the header for the WAV file
 
            MOV DX, OFFSET TEXT     ; We set the name of the new file stored in TEXT
            CALL fopen              ; We call fopen to create de file
            JC EOP                  ; Error Check

            MOV BX, AX              ; We move the file handler to BX to set the file
            MOV DI, OFFSET LA       ; We set the data to be written
            CALL Write_WAV          ; We call the function to write the sound
            JC EWRT                 ; Error Check

            CLOSE:
            CALL fclose             ; We close de file
            JC ECLS                 ; Error Check
            JMP ENDPR               ; We finish the program
            
            EOP:
            ADD AX, '0'             ; We get the ASCII code of the error
            MOV ERROR, AX           ; And store ir on the ERROR varible
            MOV DX, OFFSET ERROR    ; We set the error message stored in ERROR
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            MOV DX, OFFSET ERROR1   ; We set the error message stored in ERROR1
            INT 21H                 ; And call the interruption to print
            JMP ENDPR               ; End program
            
            EWRT:
            ADD AX, '0'             ; We get the ASCII code of the error
            MOV ERROR, AX           ; And store ir on the ERROR varible
            MOV DX, OFFSET ERROR    ; We set the error message stored in ERROR
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            MOV DX, OFFSET ERROR2
            INT 21H
            JMP CLOSE               ; Close file

            ECLS:
            ADD AX, '0'             ; We get the ASCII code of the error
            MOV ERROR, AX           ; And store ir on the ERROR varible
            MOV DX, OFFSET ERROR    ; We set the error message stored in ERROR
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            MOV DX, OFFSET ERROR3   ; We set the error message stored in ERROR3
            INT 21H                 ; And call the interruption to print
            JMP ENDPR               ; We finish the program
            
            ENDPR:
            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP
; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO

