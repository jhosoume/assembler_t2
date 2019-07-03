; %define INPUT_HEXA_ADDR DWORD [ebp + 8]

global WriteHexa

WriteHexa:
  enter 11, 0

  mov ecx, 11     ;8 digits + 2 '0X' + 1 tamanho
zeroing_loopWH:
  mov BYTE [esp + ecx], 0
  loop zeroing_loopWH

  sub ecx, ecx
  mov esi, [ebp + 8]
  mov eax, [esi]
getting_algsWH:     ;getting algarisms
  sub edx, edx
  mov ebx, 16
  div ebx        ;eax = result / edx = result

  ;cmp the rest with 10
  cmp edx, 10
  jb  sum0x30

sum0x41:
  add edx, 0x37
  jmp continueWH

sum0x30:
  add edx, 0x30

continueWH:
  mov [esp + ecx], edx

  inc ecx         ;inc stack index

  ;cmp if number is over
  cmp eax, 0
  jg getting_algsWH

end_outputWH:
  mov BYTE [esp + ecx], 0x78   ;'x'
  inc ecx
  mov BYTE [esp + ecx], 0x30   ;'0'
  inc ecx         ;ecx = size | index = size - 1
  mov [esp + 11], ecx

invert_outputWH:
  dec ECX         ;size is turned into indexes
  ;eax is teh other index
  sub eax, eax
  sub edx, edx
  sub ebx, ebx
invert_loopWH:
  ; swap positions
  mov bl, [esp + eax]   ;2
  mov dl, [esp + ecx]   ;0
  mov [esp + eax], dl
  mov [esp + ecx], bl

  inc eax
  dec ECX

  ;when indexes cross each other, stop
  cmp eax, ecx
  jb  invert_loopWH

  mov eax, 4          ;eax = 4 escrever = 3 ler
  mov ebx, 1          ;ebx arquivo a escrever 0 = teclado 1 monitor
  mov ecx, esp        ;ecx endereço
  mov edx, 10         ;edx tamanho
  int 80h

  write_enterWH:
    mov BYTE [esp], 0xA
    ; write result in the screen
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, 1
    int 80h

  leave
  ret
