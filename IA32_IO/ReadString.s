;-----------------------------------------------------
; Procedure that reads a string from the keyboard
; The value read size is return in the eax!
; nasm -f elf -o ReadString.o ReadString.s
;
;-----------------------------------------------------

; %define STRING_SIZE DWORD [ebp + 8]
; %define STRING_ADDR DWORD [ebp + 12]

global ReadString

ReadString:
    enter 0, 0

    ; get string
    mov eax, 3
    mov ebx, 0
    mov ecx, [ebp + 12]
    mov edx, [ebp + 8]
    int 80h

  breakRS:
    leave
    ret
