%define INPUT_SIZE  DWORD [esp + 11]

global ReadHexa

ReadHexa:
  enter 11, 0     ;muda a posicao do EBP tambem
  mov ecx, 11     ;10 digits + 1 sign + 1 tamanho

zeroing_loop:
  mov BYTE [esp + ecx], 0
  loop zeroing_loop

  mov eax, 3          ;eax = 4 escrever = 3 ler
  mov ebx, 0          ;ebx arquivo a escrever 0 = teclado 1 monitor
  mov ecx, esp        ;ecx endereço
  mov edx, 10         ;edx tamanho (8 digitos + 2 'x0')
  int 80h

  mov INPUT_SIZE, eax

check_last_new_line:
  ;get pointer to the last character read
  mov esi, esp
  add esi, INPUT_SIZE
  dec esi

  ;make comparision to new line ascii
  cmp BYTE [esi], 0x0A
  ;jump to next comparison if it isnt a new brk_line
  jne do_conversion
  dec BYTE INPUT_SIZE
  
do_conversion:
  sub eax, eax
  mov ecx, 2

do_conversion_loop:
  cmp ecx, INPUT_SIZE
  jge end

  shl eax, 4  ;multiply old value by 16

  sub ebx, ebx
  mov BYTE bl, [esp + ecx]
  cmp bl, 0x3A  ;if less than
  jl  sub_0x30

  sub bl, 0x37
  jmp continue

sub_0x30:
  sub bl, 0x30
continue:
  add eax, ebx

  inc ecx
  jmp do_conversion_loop

end:
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
;end program
