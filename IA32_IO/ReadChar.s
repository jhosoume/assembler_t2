;-----------------------------------------------------
; Procedure that reads a char from the keyboard
; The value read is return in the eax!
; nasm -f elf -o ReadChar.o ReadChar.s
;
;-----------------------------------------------------

%define CHAR_ADDR DWORD [ebp + 8]

global ReadChar

ReadChar:
    ; save read in the stack
    ; 12 = 10 digits + 1 sign + 1 size
    enter 1, 0

    ; get char
    mov eax, 3
    mov ebx, 0
    mov ecx, CHAR_ADDR
    mov edx, 1
    int 80h

    leave
    ret
