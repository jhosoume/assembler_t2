%define INPUT_HEXA DWORD [ebp + 8]

global WriteHexa

WriteHexa:
  enter 11, 0

  mov ecx, 11     ;8 digits + 2 '0X' + 1 tamanho
zeroing_loop:
  mov BYTE [esp + ecx], 0
  loop zeroing_loop

  sub ecx, ecx
  mov eax, INPUT_HEXA
getting_algs:     ;getting algarisms
  sub edx, edx
  mov ebx, 16
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
  jg getting_algs

end_output:
  mov BYTE [esp + ecx], 0x58   ;'x'
  inc ecx
  mov BYTE [esp + ecx], 0x30   ;'0'
  inc ecx         ;ecx = size | index = size - 1
  mov [esp + 11], ecx

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

  mov eax, 4          ;eax = 4 escrever = 3 ler
  mov ebx, 1          ;ebx arquivo a escrever 0 = teclado 1 monitor
  mov ecx, esp        ;ecx endereço
  mov edx, 10         ;edx tamanho
  int 80h

  leave
  ret
