section .data
  write DD 0xFFFE
  brk_line DB 0x0D, 0x0A

global _start

section .text
extern ReadHexa
extern WriteHexa
_start:

main:
  call ReadHexa     ;answer in EAX
  push eax
  call WriteHexa
  pop eax

  mov eax, 1
  mov ebx, 0
  int 80h
