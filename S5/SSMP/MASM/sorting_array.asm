.DATA
LIST DB 2h, 9h, 8h, 5h, 3h ; Input data
LEN DB 5                   ; Length of the list
.CODE
MOV AX, @DATA
MOV DS, AX

; Initialize variables
MOV CL, LEN                ; Outer loop counter (number of passes)
DEC CL                     ; CL = LEN - 1 (Bubble sort requires n-1 passes)

SORT_LOOP:
    MOV SI, OFFSET LIST    ; Start of the list
    MOV CH, CL             ; Inner loop counter

    INNER_LOOP:
        MOV AL, [SI]       ; Load current element
        MOV DL, [SI+1]     ; Load next element
        CMP AL, DL         ; Compare current and next
        JBE SKIP_SWAP      ; Skip if already in order

        ; Swap AL and DL
        MOV [SI], DL       ; Store next element in current position
        MOV [SI+1], AL     ; Store current element in next position

    SKIP_SWAP:
        INC SI             ; Move to the next pair
        DEC CH             ; Decrement inner loop counter
        JNZ INNER_LOOP     ; Repeat until end of list

    DEC CL                 ; Decrement outer loop counter
    JNZ SORT_LOOP          ; Repeat passes

; Output sorted list
MOV CX, LEN                ; Length of the list
MOV SI, OFFSET LIST        ; Start of the list

PRINT_LOOP:
    MOV AL, [SI]           ; Load element
    CMP AL, 0Ah            ; Check if >= 10
    JGE ALPHA              ; Convert to ASCII A-F
    ADD AL, 30h            ; Convert to ASCII 0-9
    JMP PRINT_CHAR

ALPHA:
    ADD AL, 37h            ; Convert to ASCII A-F

PRINT_CHAR:
    MOV DL, AL             ; Move to DL for printing
    MOV AH, 02h            ; DOS interrupt to print character
    INT 21h

    INC SI                 ; Move to next element
    LOOP PRINT_LOOP        ; Repeat for all elements

; Exit program
MOV AH, 4Ch
INT 21h
END
