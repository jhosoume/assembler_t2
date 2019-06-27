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
    mov ecx, [ebp + 12]
    mov edx, [ebp + 8]
    int 80h

  breakWS:
    leave
    ret
