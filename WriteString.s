;-----------------------------------------------------
; Procedure that write a string from the keyboard
; The value read is return in the eax!
; nasm -f elf -o WriteString.o WriteString.s
;
;-----------------------------------------------------

; %define INPUT_CHAR BYTE [ebp + 8]

global WriteString

WriteString:
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
