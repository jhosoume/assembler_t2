; %define INPUT_SIZE  DWORD [esp + 11]
; %define INPUT_ADDR  DWORD [ebp + 8]

global ReadHexa

ReadHexa:
  enter 11, 0     ;muda a posicao do EBP tambem
  mov ecx, 11     ;10 digits + 1 sign + 1 tamanho

zeroing_loopRH:
  mov BYTE [esp + ecx], 0
  loop zeroing_loopRH

  mov eax, 3          ;eax = 4 escrever = 3 ler
  mov ebx, 0          ;ebx arquivo a escrever 0 = teclado 1 monitor
  mov ecx, esp        ;ecx endereço
  mov edx, 10         ;edx tamanho (8 digitos + 2 'x0')
  int 80h

  mov [esp + 11], eax

check_last_new_lineRH:
  ;get pointer to the last character read
  mov esi, esp
  add esi, [esp + 11]
  dec esi

  ;make comparision to new line ascii
  cmp BYTE [esi], 0x0A
  ;jump to next comparison if it isnt a new brk_line
  jne do_conversionRH
  dec BYTE [esp + 11]

do_conversionRH:
  sub eax, eax
  ; mov ecx, 2
  mov ecx, 0

do_conversion_loopRH:
  cmp ecx, [esp + 11]
  jge endRH

  shl eax, 4  ;multiply old value by 16

  sub ebx, ebx
  mov BYTE bl, [esp + ecx]
  cmp bl, 0x3A  ;if less than
  jl  sub_0x30

  sub bl, 0x37
  jmp continueRH

sub_0x30:
  sub bl, 0x30
continueRH:
  add eax, ebx

  inc ecx
  jmp do_conversion_loopRH

endRH:
  mov esi, [ebp + 8]
  mov [esi], eax
  mov eax, [esp + 11]
  leave
  ret

;0xA3F1D
; EAX = 4(tem o enter)
;EAX = tamanho da leitura
;
;0x30, 0x58, 0x41, 0x0A
;0xFFFFFFFF
;esp + eax == 0x0A
  ;eax = eax - 1
;endRH program
