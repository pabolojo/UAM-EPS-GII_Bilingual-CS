;**************************************************************************
; MBS 2020. LAB 3
;
; Team Number XX:
;**************************************************************************

;**************************************************************************
;* BASIC ASSEMBLY PROGRAM STRUCTURE EXAMPLE to use with C code link
;* SBM / MBS 2020
;*
;**************************************************************************

; CODE SEGMENT DEFINITION
_TEXT SEGMENT BYTE PUBLIC 'CODE'
    ASSUME CS: _TEXT
    TABLE DB "TRWAGMYFPDXBNJZSQVHLCKE"

    ; First function CalculaMediana
    PUBLIC _calculaMediana
    _calculaMediana PROC FAR

        ; Push the registers used
        PUSH BP
        MOV BP, SP
        PUSH BX CX DX      

        ; Recover the data from stack , BP+6, etc (integers, pointers, etc)
        MOV AX, [BP + 6]            ; We store the four numbers in AX BX CX and DX
        MOV BX, [BP + 8]    
        MOV CX, [BP + 10]  
        MOV DX, [BP + 12]   

        ; fill in with the required instructions
        CALL SORT                   ; We "sort" the numbers putting the middle ones in AX and BX

        ; return the result in AX if needed.
        ADD AX, BX                  ; We store AX + BX in AX
        TEST AX, 1                  ; We check if is even or odd
        JZ EVENNUM
        INC AX                      ; if its odd we increment AX by one to round up
        EVENNUM:
        SAR AX, 1                   ; Once AX is even we can divide by 2, getting the result we want
        
        ; pop the used registers
        POP DX CX BX
        POP BP	                    ;BP restored
        RET

    _calculaMediana ENDP


    ; Second function enteroACadenaHexa
    PUBLIC _enteroACadenaHexa
    _enteroACadenaHexa PROC FAR

        ; Push the registers used
        PUSH BP                     ; We store the old BP on the stack
        MOV BP, SP                  ; And we set the new BP
        PUSH AX BX DX DI DS         ; We save the previous state of the registers

        ; Recover the data from stack , BP+6, etc (integers, pointers, etc)

        MOV AX, [BP + 6]            ; The number we are going to convert, we store it on AX
        LDS DI, [BP + 8]            ; The offset of the Array of chars that we store in DI


        ; fill in with the required instructions
        CALL HEX2ASCII              ; We call the function that does the conversion

        ; pop the used registers

        POP DS DI DX BX AX          ; We restore the state of the registers used
        POP BP	                    ; BP restored
        RET

    _enteroACadenaHexa ENDP


    ; Third function calculaLetraDNI
    PUBLIC _calculaLetraDNI
    _calculaLetraDNI PROC FAR

        ; Push the registered used
        PUSH BP
        MOV BP, SP
        PUSH AX BX CX DX DI SI DS ES

        ; Recover the data from stack , BP+6, etc (integers, pointers, etc)
        LDS AX, [BP + 6]
        LES DI, [BP + 10]

        ; fill in with the required instructions
        CALL GET_MOD                ; We get the reminder of the division between DNI and 23, stored in DX

        MOV SI, DX                  ; Based on the modulus that we got from the previous function
                                    ; we load the corresponding letter from the letters table to the memory
                                    ; address of the result
        MOV AL, TABLE[SI]
        MOV ES:[DI], AL

        ; pop the used registers
        POP ES DS SI DI DX CX BX AX
        POP BP	                    ;BP restored
        RET

    _calculaLetraDNI ENDP


    ;Auxiliary functions

    ; Sort the data stored in AX, BX, CX and DX putting the bigest number in DX and the lowest in CX
    SORT PROC NEAR

        CMP DX, AX      ; We compare DX with all the other registers
        JG J1
        XCHG AX, DX     ; If one of them is bigger than DX we exchange them
        J1:
        CMP DX, BX      ; So at the end DX has the bigger number
        JG J2
        XCHG BX, DX
        J2:
        CMP DX, CX
        JG J3
        XCHG CX, DX
        J3:

        CMP CX, AX      ; Now we do the same bau this time we compare CX and
        JL J4
        XCHG AX, CX     ; we exchange if some number is lower than CX
        J4:
        CMP CX, BX      ; So at the end we get the lowest number in CX
        JL J5       
        XCHG BX, CX
        J5:

        RET

    SORT ENDP

    ; Translate the number stored in AX to ASCII and stores it in the memory pointed by DI
    HEX2ASCII PROC NEAR             

        MOV DX, 0               ; We dont need the DX part of the numerator because the number is
                                ; smaller than 2**16
        MOV BX, 16              ; We set the denominator to 16
        PUSH 0                  ; And we push the last character

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
        CMP AX, 0               ; If is the last char then we finish
        JE ENDFUNC              ; jumping to the end
        JMP EXTRACT             ; If not, we extract another char

        ENDFUNC:
        RET                     ; We return when we have finished

    HEX2ASCII ENDP 

    ; Gets the reminder of the division between DNI and 23, stored in DX
    GET_MOD PROC NEAR

        MOV BP, AX              ; We initialize the variables for the loops
        MOV AX, 0
        MOV DX, 0
        MOV BX, 10
        MOV CX, BP
        ADD CX, 4


        SECOND:                 ; This loop is repeated 2 times, and it transforms the first 4 digits
                                ; from ascii to decimal and stores it in a register, and then in the stack
                                ; then it repeats for the other 4 digits
        PUSH DX
        FOR:
        MUL BX
        ADD AL, DS:[BP]         ; We get the first digit in ascii
        JNC OK
        INC AH
        OK:
        SUB AX, '0'             ; and translate it to the number it represents
        INC BP
        CMP CX, BP
        JNE FOR

        POP DX
        INC DX
        CMP DX, 2
        JE ENDF

        ADD CX, 4
        PUSH AX
        MOV AX, 0
        JMP SECOND
        ENDF:

        MOV BX, 23              ; We apply the formula (((a % 23) * (C % 23)) + (b % 23)) % 23
                                ; where a stands for the number composed by the first 4 numbers
                                ; b stands for the number composed by the last 4 numbers
                                ; and C stands for 10000 (a *C + b) = DNI
        MOV DX, 0
        DIV BX
        MOV CX, DX
        MOV DX, 0
        POP AX
        DIV BX
        PUSH CX DX

        MOV AX, 10000
        MOV DX, 0
        DIV BX
        MOV AX, DX
        POP BX
        MUL BX
        POP BX
        ADD AX, BX
        MOV BX, 23
        DIV BX                  ; Finally the result is stored in DX, thus DX = DNI % 23

        RET
    GET_MOD ENDP

_TEXT ENDS

END


