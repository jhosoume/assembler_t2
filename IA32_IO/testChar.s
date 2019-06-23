ReadChar:
    ; save read in the stack
    ; 12 = 10 digits + 1 sign + 1 size
    enter 1, 0

    ; get char
    mov eax, 3
    mov ebx, 0
    mov ecx, esp
    mov edx, 1
    int 80h

    ; move input to eax [BYTE]
    sub eax, eax
    mov al, [esp]

    leave
    ret

WriteChar:
    enter 0, 0

    mov ecx, ebp
    add ecx, 8

    ; write char
    mov eax, 4
    mov ebx, 1
    mov edx, 1
    int 80h

    leave
    ret

section .text
global _start
_start:

  call ReadChar
  ; push DWORD [write]
  push eax
  call WriteChar
  pop eax

  mov eax, 1
  mov ebx, 0
  int 80h

section .data
  write: DB "K"
