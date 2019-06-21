section .data
  write DB "**********"

section .text
extern WriteString
extern ReadString

global main
main:

  mov eax, write
  mov ebx, 10
  push eax
  push ebx
  call ReadString
  mov edx, eax
  pop ebx
  pop eax

  mov eax, write
  mov ebx, edx
  push eax
  push ebx
  call WriteString
  pop ebx
  pop eax

  mov eax, 1
  mov ebx, 0
  int 80h
