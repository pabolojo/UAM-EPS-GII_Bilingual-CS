;**************************************************************************
; MBS 2020. LAB 2
;
; Team Number XX:
;**************************************************************************

; We set the external functions that we are going to use
EXTRN fopen : FAR
EXTRN fclose : FAR
EXTRN fread : FAR

; DATA SEGMENT DEFINITION
DATOS SEGMENT

    ERROR DW 0,"$"
    ERROR1 DB "error opening file", 13, 10, "$"         ; We set in memory the strings
    ERROR2 DB "error reading file", 13, 10, "$"         ; That we are going to use
    ERROR3 DB "error closing file", 13, 10, "$"
    FILER DB "Insert the name of the file: ", 13, 10, "$"
    ANAME DB "File name: $"
    ATYPE DB " Type of archive: $"
    ASRATE DB "Sample rate (Bytes): $"
    ANSAMPLE DB "Number of samples: $"
    ANCHANNELS DB "Number of channels: $"
    ABPS DB "Bytes per second (Bytes/s): $"
    LINE DB 13, 10, '$'
    
    FILE DB 32 DUP ('0')         ; Memory for the name of the file
    BUFF DW 22 DUP(0)            ; Memory for the header of the file

    FILETYPE DW 2 DUP('$'), 13, 10, '$' ; Memory for the type
    BUFF2 DB 5 DUP('0'), 13, 10, '$'    ; Memory for the ascii representation of numbers of 2 bytes
    FILEHANDLER DW 0                    ; File handler

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

            CALL GET_DATA           ; We obatain the data

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;NAME
            MOV DX, OFFSET ANAME    ; We set the sentence we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

            MOV DX, OFFSET FILE[2]  ; We set the sentence we want to print
            INT 21H                 ; We call the interrupt to print

            MOV DX, OFFSET LINE  ; We set the sentence we want to print
            INT 21H                 ; We call the interrupt to print
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;TYPE
            MOV DX, OFFSET ATYPE    ; We set the sentence we want to print
            INT 21H                 ; We call the interrupt to print

            MOV AX, BUFF[8]         ; We store the data that we want in the registers
            MOV BX, BUFF[10]        
            MOV FILETYPE[0], AX     ; An from the registers to the variables
            MOV FILETYPE[2], BX

            MOV DX, OFFSET FILETYPE ; We set data we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; SAMPLE RATE
            MOV DX, OFFSET ASRATE   ; We set the sentence we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

            MOV DX, BUFF[26]        ; We store the data that we want in the registers
            MOV AX, BUFF[24]         
            CALL DEC_TO_ASCII_2     ; And we transform the data to ASCII

            MOV DX, OFFSET BUFF2    ; We set data we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; NSAMPLES
            MOV DX, OFFSET ANSAMPLE ; We set the sentence we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

            MOV DX, BUFF[42]        ; We store the size of the data
            MOV AX, BUFF[40]
            MOV CX, 8  
            MUL CX
            
            MOV CX, BUFF[34]
            DIV CX
            MOV BX, DX
            CALL DEC_TO_ASCII_2     ; And we transform the data to ASCII

            MOV DX, OFFSET BUFF2    ; We set data we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; NCHANNELS
            MOV DX, OFFSET ANCHANNELS ; We set the sentence we want to print
            MOV AH, 9                 ; We load the print option
            INT 21H                   ; We call the interrupt to print

            MOV AX, BUFF[22]        ; We store the data that we want in the registers      
            CALL DEC_TO_ASCII_2     ; And we transform the data to ASCII

            MOV DX, OFFSET BUFF2    ; We set data we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; BPS
            MOV DX, OFFSET ABPS     ; We set the sentence we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

            MOV DX, BUFF[30]        ; We store the data that we want in the registers
            MOV AX, BUFF[28]          
            CALL DEC_TO_ASCII_2     ; And we transform the data to ASCII

            MOV DX, OFFSET BUFF2    ; We set data we want to print
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print

            CLOSE:
            MOV BX, FILEHANDLER     ; We close de file
            CALL fclose             
            JC ECLS                 ; Error Check
            JMP ENDPR               ; We finish the program

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

            EOP:
            CALL ERROR_COM
            MOV DX, OFFSET ERROR1   ; We set the error message stored in ERROR1
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            JMP ENDPR               ; End program

            ERD:
            CALL ERROR_COM          ; We print the number of error
            MOV DX, OFFSET ERROR2   ; We set the error message stored in ERROR2
            MOV AH, 9               ; We load the print option
            INT 21H                 ; We call the interrupt to print
            JMP CLOSE               ; Close file

            ECLS:
            CALL ERROR_COM
            MOV DX, OFFSET ERROR3
            INT 21H
            JMP ENDPR               ; We finish the program
            
            ENDPR:
            ; PROGRAM END

        ;RETURN OK AND INTERRUPT
        MOV AX, 4C00H ; 00 because it's the default OK code
        INT 21H
    INICIO ENDP


    GET_DATA PROC NEAR          ; Gets the file name and the header information 

        MOV DX, OFFSET FILER    ; We set the file request message stored in FILER
        MOV AH, 9               ; We load the print option
        INT 21H                 ; We call the interrupt to print
        
        MOV AH, 0AH             ; We load the read option
        MOV DX, OFFSET FILE     ; We set the buffer for reading
        MOV FILE[0], 30         ; We set the number of characters to read 30 is our maximun (29 chars + 1 CR)
        INT 21H                 ; We call the interrupt to read

        MOV AX, 0               ; We set the next character of the string we have read
        MOV AL, FILE[1]         ; with a '$' character 
        MOV BX, OFFSET FILE
        ADD BX, AX
        MOV DS:BX[2], BYTE PTR '$'

        MOV DX, OFFSET FILE[2]  ; We set the name of the file stored in FILE[2]
        CALL fopen              ; We call fopen to open the file
        JC EOP                  ; Error Check
        MOV FILEHANDLER, AX     ; File Handler store
        
        MOV BX, AX              ; We put the file handler in BX
        MOV CX, 44              ; We set the number of bytes to read (44 is all the header)
        MOV DX, OFFSET BUFF     ; We set the buffer where the data is going to be stored
        CALL fread              ; We call the function 
        JC ERD                  ; and we check errors
        CMP AX, 44              ; We check that the number of read bytes is 44
        JNE ERD                 ; If not -> ERROR
        
        RET

    GET_DATA ENDP 

    DEC_TO_ASCII_2 PROC NEAR    ; Transform AX into ASCII stored in BUFF2

        CALL RESET_BUFF2        ; We put the buffer to '$' characters
        MOV DX, 0               ; We dont need the DX part of the numerator because in 
                                ; Moodle you said that the numerator will be smaller than 2**16
        MOV BX, 10              ; We set the divisor = 10
        MOV BP, OFFSET BUFF2[5] ; and the base pointer to the units byte
        MOV CX, OFFSET BUFF2    ; This is the last byte that we must write, we sotore it on CX

        FOR2:
        DIV BX                  ; We divide AX by 10
        ADD DX, '0'             ; We convert the reminder to ASCII
        MOV DS:BP[0], DL        ; And we store it in the buffer
        CMP CX, BP              ; We check if is the last byte of the buffer
        JE ENDFOR2              ; If it is, we finish
        MOV DX, 0               ; Else we reset DX
        DEC BP                  ; And go to the next byte of the buffer
        JMP FOR2                ; And repeat the loop
        ENDFOR2:

        RET                     ; We return when we have finished

    DEC_TO_ASCII_2 ENDP 

    RESET_BUFF2 PROC NEAR

        MOV BUFF2[0], '$'   ; We set the chars to '$'
        MOV BUFF2[1], '$'
        MOV BUFF2[2], '$'
        MOV BUFF2[3], '$'
        MOV BUFF2[4], '$'
        MOV BUFF2[5], '$'

        RET                 ; We return when  we have finished

    RESET_BUFF2 ENDP 

    ERROR_COM PROC NEAR
        ADD AX, '0'             ; We get the ASCII code of the error
        MOV ERROR, AX           ; And store ir on the ERROR varible
        MOV DX, OFFSET ERROR    ; We set the error message stored in ERROR
        MOV AH, 9               ; We load the print option
        INT 21H                 ; We call the interrupt to print
        RET
    ERROR_COM ENDP

; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END INICIO

