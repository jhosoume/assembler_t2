;-----------------------------------------------------
; Procedure that write a char in the screen from number in stack
; The value read is return in the eax!
; nasm -f elf -o WriteChar.o WriteChar.s
;
;-----------------------------------------------------

; %define INPUT_CHAR BYTE [ebp + 8]

global WriteChar

WriteChar:
    enter 0, 0

    mov ecx, ebp
    add ecx, 8

    ; write char
    mov eax, 4
    mov ebx, 1
    mov edx, 1
    int 80h

  break:
    leave
    ret
