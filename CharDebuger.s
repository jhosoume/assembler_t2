section .data
  write DB "K"

section .text
extern WriteChar
extern ReadChar

global main
main:

  call ReadChar
  ; push DWORD [write]
  push eax
  call WriteChar
  pop eax

  mov eax, 1
  mov ebx, 0
  int 80h
