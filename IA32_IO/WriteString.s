;-----------------------------------------------------
; Procedure that write a string from the keyboard
;
; nasm -f elf -o WriteString.o WriteString.s
;
;-----------------------------------------------------

%define STRING_SIZE DWORD [ebp + 8]
%define STRING_ADDR DWORD [ebp + 12]

global WriteString

WriteString:
    enter 0, 0

    ; write string
    mov eax, 4
    mov ebx, 1
    mov ecx, STRING_ADDR
    mov edx, STRING_SIZE
    int 80h

  break:
    leave
    ret
