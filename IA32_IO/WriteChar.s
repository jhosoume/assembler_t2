;-----------------------------------------------------
; Procedure that write a char in the screen from number in stack
; The value read is return in the eax!
; nasm -f elf -o WriteChar.o WriteChar.s
;
;-----------------------------------------------------

%define CHAR_ADDR DWORD [ebp + 8]

global WriteChar

WriteChar:
    enter 1, 0

    ; write char
    mov eax, 4
    mov ebx, 1
    mov ecx, CHAR_ADDR
    mov edx, 1
    int 80h

  write_enterWC:
    mov BYTE [esp], 0xA
    ; write result in the screen
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, 1
    int 80h

    leave
    ret
