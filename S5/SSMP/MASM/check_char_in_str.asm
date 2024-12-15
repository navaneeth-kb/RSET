.model small
.stack 100h
.data
    msg1 db 'Found$', 0
    msg2 db 'Not found$', 0
    inp1 db 'Input String: $', 0
    inp2 db 10, 13, 'Input Character: $', 0
    buffer db 50  ; Max string length
           db ?          ; Actual length will be stored here
           db 50 dup(?)  ; Space for the input string
.code
start:
    mov ax, @data
    mov ds, ax

    ; Prompt for input string
    lea dx, inp1
    mov ah, 09h
    int 21h

    lea dx, buffer
    mov ah, 0Ah
    int 21h

    ; Prompt for input character
    lea dx, inp2
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    mov bl, al  ; Store the input character in BL

    ; Set SI to the start of the input string
    lea si, buffer + 2  ; Skip length byte and actual length byte
    mov cl, buffer[1]   ; Get the actual length of the string

check:
    lodsb               ; Load next character from string into AL
    cmp al, bl          ; Compare with input character
    je found            ; If match, jump to found
    loop check          ; Otherwise, continue looping

notFound:
    lea dx, msg2
    mov ah, 09h
    int 21h
    jmp final

found:
    lea dx, msg1
    mov ah, 09h
    int 21h

final:
    mov ah, 4Ch
    int 21h
end start
