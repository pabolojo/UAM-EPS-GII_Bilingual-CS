;**************************************************************************
; MBS 2020. LAB 4
;
; p4c.asm  Code for the last exercise of the LAB4
;
; Team Number XX:
;**************************************************************************

; DATA SEGMENT DEFINITION
DATOS SEGMENT
    BUFFOUT DB 6 dup(0)         ; Buffer for the result of the 55h int
    OPTION DB 13 dup(?), '$'    ; Buffer for the input from keyboard

    ; Strings for user information
    PRINT1 DB "Enter an option (quit hex dec) and a number", 13, 10, "(Hexadecimal numbers should be on capital letters):", 13, 10, '$'
    PRINT2 DB "Incorrect option. Exiting...", 13, 10, '$'
    PRINT3 DB 13, 10, "$"
DATOS ENDS
;**************************************************************************

; STACK SEGMENT DEFINITION
PILA SEGMENT STACK "STACK"
    DB 40H DUP (0)
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

                WHILE:
                CALL GET_DATA               ; We obtain the data

                CMP BX, 0                   ; We check if we are in "quit", "hex" or "dec" option
                JE PEND                     ; jumping to the correspondent section
                CMP BX, 2
                JE DECI

                HEX:                        ; If is HEX or DEC we set AH to the correspondent value
                MOV AH, 10h     
                JMP STRR
                DECI:
                MOV AH, 11h
                
                STRR:
                MOV CX, OFFSET OPTION[6]    ; We prepare the input and the output for the
                MOV DX, OFFSET BUFFOUT      ; 55h interruption and we call it
                INT 55h

                MOV AH, 2H                  ; Now we prepare 21H int to print one single char
                MOV DI, 0                   ; we set the offset of the buffer to 0
                MOV BX, 0                   ; We set ES to 0
                MOV ES, BX
                LES SI, ES:[55h * 4]        ; Whe check if the flag is activated
                MOV BYTE PTR ES:[SI - 7], 0 ; And the FLAG to 0 also
                
                WAITT:
                CMP BYTE PTR ES:[SI - 7], 0       
                JE WAITT                    ; If is not we still waiting

                MOV BYTE PTR ES:[SI - 7], 0 ; If it is, we desactivate it
                MOV DL, BUFFOUT[DI]         ; We store the digit we want to print
                CMP DL, '$'                 ; checking that is not the last one
                JE PRINTCRLF                ; If it is we print CR LF ant return

                INT 21H                     ; If not, we print the char
                INC DI                      ; And we point the next char we want to print
                JMP WAITT                   ; And wait for the flag to activate

                PRINTCRLF:
                MOV AH, 9H                  ; We set that want to print a string
                MOV DX, OFFSET PRINT3       ; We set the message to print
                INT 21H                     ; we print it
                JMP WHILE                   ; and we ask for another instruction

                PEND:                       ; If is the "quit" option we end the program

            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP

    ; BEGINNING OF THE FUNCTION GET_DATA 
    GET_DATA PROC
        MOV AH, 9                           ; We load the print option
        MOV DX, OFFSET PRINT1               ; We set the message to print
        INT 21H                             ; We call the interrupt to print

        MOV AH, 0AH                         ; We load the read option
        MOV DX, OFFSET OPTION               ; We set the buffer for reading
        MOV BYTE PTR OPTION[0], 11          ; We set the number of characters to read 11 is our maximun
        INT 21H                             ; We call the interrupt to read
        MOV BL, OPTION[1]                   ; We get the number of chars read
        MOV BH, 0
        MOV OPTION[BX + 2], '$'             ; And we set the last char to $

        MOV AH, 9                           ; We load the print option
        MOV DX, OFFSET PRINT3               ; We set the message to print (CR LF)
        INT 21H                             ; We call the interrupt to print

        CALL CHECK_QUIT                     ; We check what option has the instruction
        JC QUIT                             ; jumping to the required part of the code
        CALL CHECK_DEC
        JC DECA
        CALL CHECK_HEX
        JC HEXA

        ; If is not a valid option
        MOV AH, 9                           ; We load the print option
        MOV DX, OFFSET PRINT2               ; We set the message to print (INVALID OPTION)
        INT 21H                             ; We call the interrupt to print
                                            ; and we exit

        ; If is a valid option
        QUIT:                               ; We return the value that we are going to 
        MOV BX, 0                           ; compare in the main program
        JMP ENDPP
        DECA:
        MOV BX, 2
        JMP ENDPP
        HEXA:
        MOV BX, 1
        ENDPP:
        RET
    GET_DATA ENDP

    CHECK_QUIT PROC NEAR
        MOV AX, WORD PTR OPTION[2]          ; We set the 4 bytes that we have read 
        MOV BX, WORD PTR OPTION[4]          ; in the AX and BX registers
        XOR AX, "uq"                        ; We compare this registers with the word
        XOR BX, "ti"                        ; "quit" stored in little endian
        OR AX, BX                           ; We do that with XOR and OR instructions and CMP
        CMP AX, 0                    
        JNE ENDQUIT                         ; If isn't quit we continue
        STC                                 ; else we set the carry flag to one
        ENDQUIT:                    
        RET                                 ; and we return
    CHECK_QUIT ENDP

    CHECK_HEX PROC NEAR
        MOV AX, WORD PTR OPTION[2]          ; We set the 4 bytes that we have read 
        MOV BX, WORD PTR OPTION[4]          ; in the AX and BX registers
        XOR AX, "eh"                        ; We compare this registers with the word
        XOR BX, " x"                        ; "hex" stored in little endian
        OR AX, BX                           ; We do that with XOR and OR instructions and CMP
        CMP AX, 0                        
        JNE ENDQUITH                        ; If isn't quit we continue
        STC                                 ; else we set the carry flag to one
        ENDQUITH:                    
        RET                                 ; and we return
    CHECK_HEX ENDP 
    CHECK_DEC PROC NEAR
        MOV AX, WORD PTR OPTION[2]          ; We set the 4 bytes that we have read 
        MOV BX, WORD PTR OPTION[4]          ; in the AX and BX registers
        XOR AX, "ed"                        ; We compare this registers with the word
        XOR BX, " c"                        ; "dec" stored in little endian
        OR AX, BX                           ; We do that with XOR and OR instructions and CMP
        CMP AX, 0                    
        JNE ENDQUITD                        ; If isn't quit we continue
        STC                                 ; else we set the carry flag to one
        ENDQUITD:                   
        RET                                 ; and we return
    CHECK_DEC ENDP 
; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO


