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
    ERROR1 DB "error opening file", 13, 10, "$"     ; We set the error messages
    ERROR2 DB "error writing WAV", 13, 10, "$"      
    ERROR3 DB "error closing file", 13, 10, "$"
    ERROR DW 0,"$"
    FILER DB "Name of the file:", 13, 10, "$"       ; the information messages
    FREQR DB "Frecuency of the note:", 13, 10, "$"
    FILE DB 14 DUP (0), 0                           ; and buffers for the data
    FREQ DB 6 DUP (0)
    RATIOA DW 0
    RATIOB DW 0
    TONE DB 8000 DUP (?)
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
        WHILEP:                     ; While loop because we want to repeat the program until "quit" is recived

            CALL GET_INPUT          ; we get the input data
            JC TOTALEND

            CALL CALC_RATIO         ; we calc the ratio of change of the calues of the samples

            CALL CREATE_TABLE       ; And we create the data we want
            
            MOV AX, 0               ; We put the last byte of the name of the file to 0
            MOV AL, FILE[1]   
            MOV BX, OFFSET FILE
            ADD BX, AX
            MOV DS:BX[2], BYTE PTR 0

            MOV DX, 8000            ; We set the sample rate
            MOV CX, 8000            ; We set the number of samples
            CALL Init_WAV_Header    ; We create the header for the WAV file
 
            MOV DX, OFFSET FILE[2]  ; We set the name of the new file stored in TEXT
            CALL fopen              ; We call fopen to create de file
            JC EOP                  ; Error Check

            MOV BX, AX              ; We move the file handler to BX to set the file
            MOV DI, OFFSET TONE     ; We set the data to be written
            CALL Write_WAV          ; We call the function to write the sound
            JC EWRT                 ; Error Check

            CLOSE:
            CALL fclose             ; We close de file
            JC ECLS                 ; Error Check
            JMP ENDPR               ; We finish the program
            
            EOP:                    
            CALL ERROR_COM          ; We print the error number
            MOV DX, OFFSET ERROR1
            INT 21H
            JMP ENDPR               ; End program
            
            EWRT:
            CALL ERROR_COM
            MOV DX, OFFSET ERROR2
            INT 21H
            JMP CLOSE               ; Close file

            ECLS:
            CALL ERROR_COM
            MOV DX, OFFSET ERROR3
            INT 21H
            JMP ENDPR               ; We finish the program
            
            ENDPR:
            JMP WHILEP              ; We return to the while because we only finish with the quit option
            TOTALEND:
            
            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP

    ASCCI_TO_DEC PROC NEAR

        MOV AX, 0           ; We initialize AX
        MOV AL, FREQ[2]     ; We get the first digit in ascii
        SUB AX, '0'         ; and translate it to the number it represents
        MOV BL, 100         ; We multiply this digit by 100
        MUL BL              ; and add it to the result
        MOV CX, AX          ; stored in CX

        MOV AL, FREQ[3]     ; We get the second digit in ascii
        SUB AX, '0'         ; and translate it to the number it represents
        MOV BL, 10          ; We multiply this digit by 10
        MUL BL              ; and add it to the result
        ADD CX, AX          ; stored in CX

        MOV AL, FREQ[4]     ; We get the second digit in ascii
        SUB AX, '0'         ; and translate it to the number it represents
        ADD CX, AX          ; and add it to the result 
        RET                 ; We return when  we have finished
    ASCCI_TO_DEC ENDP 

    CHECK_QUIT PROC NEAR
        MOV AX, WORD PTR FILE[2]    ; We set the 4 bytes that we have read 
        MOV BX, WORD PTR FILE[4]    ; in the AX and BX registers
        XOR AX, "uq"                ; We compare this registers quit the word
        XOR BX, "ti"                ; "quit" stored in little endian
        OR AX, BX                   ; We do that with XOR and OR instructions and CMP
        CMP AX, 0                   ; 
        JNE ENDQUIT                 ; If isn't quit we continue
        STC                         ; else we set the carry flag to one
        ENDQUIT:                    ;
        RET                         ; and we return
    CHECK_QUIT ENDP 

    CREATE_TABLE PROC NEAR
    ; We initialice the variables that we will use in the FOR
            MOV RATIOA, AX          ; We store the ratio in memory
            MOV RATIOB, BX          ; We store the ratio in memory

            MOV AX, 0               ; We initialice the variables
            MOV BP, OFFSET TONE     ; that we will use in the FOR
            
            WHILE:
            MOV BX, 0               ; With this while we fill the array of 
            FORP:                   ; data of the sound wave. RatioA samples for the value 50
                CMP BX, RATIOA      ; and ratioB samples for the value -50
                JE ENDFORP
                MOV CX, 50
                MOV DS:BP, CL
                INC BX
                INC BP
                INC AX
                CMP AX, 8000
                JE ENDWHILE
                JMP FORP
            ENDFORP:
                MOV BX, 0
            FORN:
                CMP BX, RATIOB
                JE WHILE
                MOV CX, -50
                MOV DS:BP, CL
                INC BX
                INC BP
                INC AX
                CMP AX, 8000
                JE ENDWHILE
                JMP FORN
            ENDWHILE:
            RET
    CREATE_TABLE ENDP

    GET_INPUT PROC NEAR
        MOV DX, OFFSET FILER    ; We set the file request message stored in FILER
        MOV AH, 9               ; We load the print option
        INT 21H                 ; We call the interrupt to print
        
        MOV AH, 0AH             ; We load the read option
        MOV DX, OFFSET FILE     ; We set the buffer for reading
        MOV FILE[0], 12         ; We set the number of characters to read 12 is our maximun
        INT 21H                 ; We call the interrupt to read
        CALL CHECK_QUIT         ; We check the "quit" option
        JC QUIT                 ; If is the "quit" option, we finish the program

        MOV DX, OFFSET FREQR    ; We set the frecuency request message stored in FREQR
        MOV AH, 9               ; We load the print option
        INT 21H                 ; We call the interrupt to print
        
        MOV AH, 0AH             ; We load the read option
        MOV DX, OFFSET FREQ     ; We set the buffer for reading
        MOV FREQ[0], 5          ; We set the number of characters to read 4 for "QUIT" + 1 for CR
        INT 21H                 ; We call the interrupt to read
        CALL ASCCI_TO_DEC       ; We decode the frecuency
        
        QUIT:
        RET
    GET_INPUT ENDP

    ERROR_COM PROC NEAR
        ADD AX, '0'
        MOV ERROR, AX
        MOV DX, 0
        MOV DX, OFFSET ERROR    ; We set the error message stored in ERROR
        MOV AH, 9               ; We load the print option
        INT 21H                 ; We call the interrupt to print
        RET
    ERROR_COM ENDP

    CALC_RATIO PROC NEAR
            MOV DX, 0               ; We put DX to 0 because the divisor is 16 bits long
            MOV AX, 8000            ; We set 8000 in AX, this is the dividend
            DIV CX                  ; We divide DX:AX by CX
            
            SHR CX, 1               ; We divide CX by 2 to recover the frecuency
            CMP CX, DX              ; If the reminder of the division is greater than the
            JGE NOTSUM              ; frecuency, we add 1 to the ratio (We are rounding the division)
            INC AX
            NOTSUM:                 
            MOV BX, AX
            SHR BX, 1
            SHL BX, 1
            XOR BX, AX
            SHR AX, 1
            CMP BX, 0
            MOV BX, AX
            JE EVENNUM
            INC BX
            EVENNUM:
            RET
    CALC_RATIO ENDP

; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO

