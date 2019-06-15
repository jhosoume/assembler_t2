section .data
  input DD 0
  write DD 0xFFFE
  brk_line DB 0x0D, 0x0A
  size  DB 0

global _start
section .text
_start:

prepare_stack:
  sub esp, 13
  mov ecx, 12     ;10 digits + 1 sign + 1 tamanho

zeroing_loop:
  mov BYTE [esp + ecx], 0
  loop zeroing_loop

  sub ecx, ecx
  mov ebx, 16
  mov eax, [write]
getting_algs:     ;getting algarisms
  cdq             ;sign extention
  div ebx        ;eax = result / edx = result

  ;cmp the rest with 10
  cmp edx, 10
  JB  sum0x30

sum0x41:
  add edx, 0x37
  JMP continue

sum0x30:
  add edx, 0x30

continue:
  mov [esp + ecx], edx

  inc ecx         ;inc stack index

  ;cmp if number is over
  cmp eax, 0
  JNE getting_algs

end_output:
  mov BYTE [esp + ecx], 0x58   ;'x'
  inc ecx
  mov BYTE [esp + ecx], 0x30   ;'0'
  inc ecx         ;ecx = size | index = size - 1
  mov [esp + 12], ecx

invert_output:
  dec ECX         ;size is turned into indexes
  ;eax is teh other index
  sub eax, eax
  sub edx, edx
  sub ebx, ebx
invert_loop:
  ; swap positions
  mov bl, [esp + eax]   ;2
  mov dl, [esp + ecx]   ;0
  mov [esp + eax], dl
  mov [esp + ecx], bl

  inc eax
  dec ECX

  ;when indexes cross each other, stop
  cmp eax, ecx
  JB  invert_loop

WriteHexa:
  mov eax, 4          ;eax = 4 escrever = 3 ler
  mov ebx, 1          ;ebx arquivo a escrever 0 = teclado 1 monitor
  mov ecx, esp        ;ecx endereço
  mov edx, 12         ;edx tamanho
  int 80h

  add esp, 13

  mov eax, 4
  mov ebx, 1
  mov ecx, brk_line
  mov edx, 2
  int 80h

  mov eax, 1
  mov ebx, 0
  int 80h
