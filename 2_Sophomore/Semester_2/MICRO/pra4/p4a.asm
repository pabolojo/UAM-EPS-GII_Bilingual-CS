;**************************************************************************
; MBS 2020. LAB 4
;
; p4b.asm
;
; Team Number XX:
;**************************************************************************

; CODE SEGMENT DEFINITION
CODE SEGMENT
    ASSUME CS: CODE
    ORG 256

    start: jmp CHECK_ARGUMENTS

    ; Variables we are going to use
    COUNTER DB 0
    FLAGC DB 0
    OLDVECTOR DW 0,0
    SIGN DW 0ABCDh
    
    ; BEGINNING OF THE FUNCTION ISR
    ISR PROC

        STI
        PUSH BP
        PUSH AX BX CX DI SI DX
        MOV BP, SP

        CMP AH, 10h                     ; We check the AH low byte to know what options we have to execute
        JNE AUX1
        CALL DECI2HEX
        JMP ENDISR

        AUX1:
        CMP AH, 11h
        JNE ENDISR
        CALL HEX2DECI

        ENDISR:
        POP DX SI DI CX BX AX
        POP BP

        IRET

    ISR ENDP

    ; BEGINNING OF THE FUNCTION ISR
    ISR_T PROC

        PUSH AX                         ; We save the data of AX

        IN AL, 021h                     ; Read IMR from the master PIC
        AND AL, 11111110b               ; Disable inhibition bit for pin IR0 (Timer)
        OUT 021h, AL                    ; Modify IMR of the master PIC   

        MOV AL, COUNTER                 ; We load the counter variable
        INC AL                          ; And increment it
        CMP AL, 18                      ; If is 18 we continue
        JE FLAGG        
        JMP ENDISRT                     ; else we wait untill is 18
        
        FLAGG:
        MOV AL, 0                       ; We reset the counter
        MOV FLAGC, 1                    ; And activate the flag

        ENDISRT:
        MOV COUNTER, AL                 ; We save the changed data
        POP AX                          ; We recover the data of BX

        IRET

    ISR_T ENDP

        ; BEGINNING OF THE FUNCTION DECI2HEX
    DECI2HEX PROC

        CALL ATOI

        MOV DI, [BP]

        MOV DX, 0               ; We dont need the DX part of the numerator because the number is
                                ; smaller than 2**16
        MOV BX, 16              ; We set the denominator to 16
        PUSH "0$"               ; And we push the last character

        FOR2:
        DIV BX                  ; We divide AX by 16

        CMP DX, 9               ; We compare with 9 because we want to know
        JG LETTER               ; if is the ascii of the char is a letter or a number

        ADD DX, '0'             ; We convert the reminder to ASCII adding '0'
        JMP CNT                 ; And we jump to continue the function

        LETTER:
        ADD DX, '7'             ; 7 Because '7' + 10 = 'A' in ASCII

        CNT:
        PUSH DX                 ; And we store it in the stack
        CMP AX, 0               ; We check if there is no more to divide
        JE EXTRACT              ; If it is the case, we extract from the stack and finish
        MOV DX, 0               ; Else we reset DX
        JMP FOR2                ; And repeat the loop

        EXTRACT:
        POP AX                  ; We extract the char
        MOV [DI], AX            ; And store it on the direccion needed
        INC DI                  ; And point to the next char
        CMP AX, "0$"            ; If is the last char then we finish
        JE ENDFUNC              ; jumping to the end
        JMP EXTRACT             ; If not, we extract another char

        ENDFUNC:

        RET                     ; We return when we have finished
    DECI2HEX ENDP
    
    ATOI PROC

        MOV AX, 0
        MOV BL, 10
        MOV DI, CX
        MOV SI, CX
        MOV CX, 0

        START_ATOI:
        MOV CL, BYTE PTR [SI]
        CMP CL, "$"
        JZ END_ATOI

        MUL BX
        ADD AX, CX

        SUB AX, '0'
        INC SI
        
        JMP START_ATOI
        END_ATOI:

        MOV CX, DI

        RET
        
    ATOI ENDP

    ; BEGINNING OF THE FUNCTION HEX2DECI
    HEX2DECI PROC

        CALL HEXATOI

        MOV DI, [BP]

        MOV DX, 0               ; We dont need the DX part of the numerator because the number is
                                ; smaller than 2**16
        MOV BX, 10              ; We set the denominator to 10
        PUSH "0$"                  ; And we push the last character

        FOR2HEX:
        DIV BX                  ; We divide AX by 10
        ADD DX, '0'             ; We convert the reminder to ASCII adding '0'

        CNTHEX:
        PUSH DX                 ; And we store it in the stack
        CMP AX, 0               ; We check if there is no more to divide
        JE EXTRACTHEX              ; If it is the case, we extract from the stack and finish
        MOV DX, 0               ; Else we reset DX
        JMP FOR2HEX                ; And repeat the loop

        EXTRACTHEX:
        POP AX                  ; We extract the char
        MOV [DI], AX            ; And store it on the direccion needed
        INC DI                  ; And point to the next char
        CMP AX, "0$"               ; If is the last char then we finish
        JE ENDFUNCHEX              ; jumping to the end
        JMP EXTRACTHEX             ; If not, we extract another char

        ENDFUNCHEX:
        RET                     ; We return when we have finished
    HEX2DECI ENDP

    HEXATOI PROC
        MOV AX, 0
        MOV BX, 16
        MOV DI, CX
        MOV SI, CX
        MOV CX, 0

        START_HEXATOI:
        MOV CL, BYTE PTR [SI]
        CMP CL, "$"
        JZ END_HEXATOI

        MUL BX
        ADD AX, CX

        CMP CL, "A"
        JAE LETTER_HEX
        SUB AX, '0'
        JMP CNT_HEX
        
        LETTER_HEX:
        SUB AX, '7'

        CNT_HEX:
        INC SI
        
        JMP START_HEXATOI
        END_HEXATOI:

        MOV CX, DI

        RET
        
    HEXATOI ENDP

    CHECK_ARGUMENTS PROC

        CMP CS:[80h], BYTE PTR 0    ; We check if there is not arguments 
        JNZ CHECK                   
        CALL STATUS                 ; In that case we call the status function
        JMP EXIT
        
        CHECK:
        CMP CS:[80h], BYTE PTR 3    ; We check if the size of the argument is 2 chars
        JNZ ERROR
        CMP CS:[82h], "I/"          ; We check if is /I or /U
        JNZ NINS
        CALL INSTALL                ; And we call the correspondent function
        JMP EXIT

        NINS:
        CMP CS:[82h], "U/"
        JNZ ERROR
        CALL UNINSTALL
        JMP EXIT
        ; PROGRAM END
        ERROR:                      ; If the argument is not empty, /I or /U we return
        CALL ERRORM

        EXIT:
        MOV AX,4C00H
	    INT 21H

    CHECK_ARGUMENTS ENDP
    
    ; We define the data we are going to use
    DB "Execute the program with /I to install the driver or /U to uninstall", 13, 10
    DB "Calling INT 55h with AX = 10h performs DEC to HEX and with AX = 11h HEX to DEC", 13, 10
    DB "DS:CX should point the target string and DS:DX to the result string", 13, 10
    DB "Status of the driver: $"

    INSTALLED DB "Installed", 13, 10, '$'
    UNINSTALLED DB "Uninstalled", 13, 10, '$'

    ; BEGINNING OF THE FUNCTION STATUS
    STATUS PROC
        
        MOV DX, OFFSET INFO             ; We set the error message stored in INFO
        MOV AH, 9                       ; We load the print option
        INT 21H                         ; We call the interrupt to print

        MOV CX, 0                       ; We check if the driver is already installed
        MOV ES, CX
        LES SI, ES:[55h * 4]
        CMP ES:[SI - 2], 0ABCDh
        JNZ NO

        YES:
        MOV DX, OFFSET INSTALLED        ; We set the error message stored in INFO
        MOV AH, 9                       ; We load the print option
        INT 21H                         ; We call the interrupt to print
        JMP ENDSTATUS
        
        NO:
        MOV DX, OFFSET UNINSTALLED      ; We set the error message stored in INFO
        MOV AH, 9                       ; We load the print option
        INT 21H                         ; We call the interrupt to print

        ENDSTATUS:
        RET

    STATUS ENDP

    ERRORIM DB "Driver already installed. Exiting...", 13, 10, '$'
    INSTALLEDS DB "Driver installed successfully. Exiting...", 13, 10, '$'
    ; BEGINNING OF THE FUNCTION INSTALL
    INSTALL PROC

        MOV AX, 0
        MOV ES, AX
        LES SI, ES:[55h * 4]
        CMP ES:[SI - 2], 0ABCDh
        JNZ NERRORI
        MOV DX, OFFSET ERRORIM   ; We set the error message stored in ERRORIM
        MOV AH, 9                ; We load the print option
        INT 21H                  ; We call the interrupt to print
        RET
        
        NERRORI:
        MOV AX, 0
        MOV ES, AX
        MOV AX, OFFSET ISR
        MOV BX, CS

        CLI
        MOV ES:[55h*4], AX
        MOV ES:[55h*4 + 2], BX
        STI

        LES SI, ES:[1Ch * 4]
        MOV OLDVECTOR, SI
        MOV OLDVECTOR[2], ES

        MOV CX, 0
        MOV ES, CX
        MOV CX, OFFSET ISR_T

        IN AL, 021h         ; Read IMR from the master PIC
        OR AL, 00000001b    ; Activate inhibition bit for pin IR0 (Timer)
        OUT 021h, AL        ; Modify IMR of the master PIC

        MOV ES:[1Ch*4], CX
        MOV ES:[1Ch*4 + 2], BX

        IN AL, 021h         ; Read IMR from the master PIC
        AND AL, 11111110b   ; Disable inhibition bit for pin IR0 (Timer)
        OUT 021h, AL        ; Modify IMR of the master PIC     
        
        MOV DX, OFFSET INSTALLEDS       ; We set the error message stored in INFO
        MOV AH, 9                       ; We load the print option
        INT 21H                         ; We call the interrupt to print

        MOV DX, OFFSET CHECK_ARGUMENTS
        INT 27H
        
    INSTALL ENDP

    ERRORUM DB "Driver not installed. Exiting...", 13, 10, '$'
    UNINSTALLEDS DB "Driver uninstalled successfully. Exiting...", 13, 10, '$'
    ; BEGINNING OF THE FUNCTION UNINSTALL
    UNINSTALL PROC
    
        MOV AX, 0
        MOV ES, AX

        LES SI, ES:[55h * 4]

        CMP SI, 0                ; We check that the driver is installed
        JZ NOTINSTALLED

        CMP ES:[SI - 2], 0ABCDh
        JZ NERRORU
        NOTINSTALLED:
        MOV DX, OFFSET ERRORUM   ; We set the error message stored in ERRORUM
        MOV AH, 9                ; We load the print option
        INT 21H                  ; We call the interrupt to print
        RET
        
        NERRORU:
        MOV ES:[SI - 2], WORD PTR 0
        MOV AX, 0
        MOV ES, AX
        MOV ES, ES:[55h * 4 + 2]
        MOV BX, ES:[2Ch]

        MOV DI, DS
        MOV DS, AX
        LDS SI, DS:[55h * 4]

        ;-6 offset -4 segment
        MOV CX, DS:[SI - 6]
        MOV DX, DS:[SI - 4]

        MOV AH, 49h
        INT 21h
        MOV ES, BX
        INT 21h

        MOV AX, 0
        MOV ES, AX

        CLI
        MOV ES:[55h*4], AX
        MOV ES:[55h*4 + 2], AX
        MOV ES:[1Ch*4], CX
        MOV ES:[1Ch*4 + 2], DX
        STI
        
        MOV DS, DI
        MOV DX, OFFSET UNINSTALLEDS     ; We set the error message stored in INFO
        MOV AH, 9                       ; We load the print option
        INT 21H                         ; We call the interrupt to print

        RET

    UNINSTALL ENDP

    ERRORME DB "Invalid argument. Exiting...", 13, 10, '$'
    ; BEGINNING OF THE FUNCTION ERRORM
    ERRORM PROC
        MOV DX, OFFSET ERRORME   ; We set the error message stored in ERRORME
        MOV AH, 9                ; We load the print option
        INT 21H                  ; We call the interrupt to print
        RET
    ERRORM ENDP

; END OF CODE SEGMENT
CODE ENDS

; END OF PROGRAM. OBS: INCLUDES THE ENTRY OR THE FIRST PROCEDURE (i.e. “INICIO”)
END start

