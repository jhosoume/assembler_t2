section .data
  write DD "K"

section .text
extern WriteChar
extern ReadChar

global main
main :

  push DWORD write
  call ReadChar
  ; push DWORD [write]
  call WriteChar
  pop edx

  mov eax, 1
  mov ebx, 0
  int 80h
