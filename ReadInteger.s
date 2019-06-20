;-----------------------------------------------------
; Procedure that reads an integer from the keyboard
; The value read is return in the eax!
; nasm -f elf -o ReadInteger.o ReadInteger.s
;
;-----------------------------------------------------

%define INPUT_SIZE DWORD [esp + 11]

global ReadInteger

ReadInteger:
    ; save read in the stack
    ; 12 = 10 digits + 1 sign + 1 size
    enter 12, 0

    ; zero stack positions
    mov ecx, 12
  zeroing_loop:
    mov BYTE [esp + ecx], 0
    loop zeroing_loop

    ; get all numbers
    mov eax, 3
    mov ebx, 0
    mov ecx, esp
    mov edx, 11
    int 80h

    ; save numbers read
    mov INPUT_SIZE, eax

  check_minus:

    ; get pointer to the last character read
    mov edi, esp
    add edi, INPUT_SIZE
    dec edi

    ; check if last is a new line 
    cmp BYTE [edi], 0xA
    jne continue_here

    mov BYTE [esp], 0x57
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, 1
    int 80h

  continue_here:
    ; print numbers just to see
    mov eax, 4
    mov ebx, 1
    mov ecx, edi
    mov edx, 1
    int 80h

    mov eax, INPUT_SIZE

  break:
    leave
    ret
