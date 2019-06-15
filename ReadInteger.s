section .data
  input DD 0
  write DD 123748
  output DB 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  negative_msg DB "Found neg", 0h
  size_neg EQU $-negative_msg

; section .bss
;   output resb 70

global _start
section .text
_start:
  ; Get input value and stores in input
  ; mov eax, 3
  ; mov ebx, 0
  ; mov ecx, input
  ; mov edx, 4
  ; int 80h
;
;   cmp byte [input], 45
;   jne continue
; print_neg:
;   mov eax, 4
;   mov ebx, 1
;   mov ecx, negative_msg
;   mov edx, size_neg
;   int 80h

WriteInteger:
  ; Zero Index, ECX = indx
  ; Value = Write
  sub ecx, ecx
  ; save result in the stack
  sub esp, 13
convert_loop:
  ; Gets value divided by ten
  ; Dividend
  mov eax, [write]
  cdq
  ; Divisor
  mov ebx, 10
  ; eax will have the quotient
  ; edx will have the rest
  idiv ebx

  ;output [indx] = (char) ((value % 30) + 0x30)
  add BYTE dl, 0x30
  mov BYTE [esp + ecx], dl

  ;value = value/10
  mov [write], eax

  ; ; write test
  ; mov eax, 4
  ; mov ebx, 1
  ; push ecx
  ; mov ecx, write
  ; mov edx, 1
  ; int 80h
  ; pop ecx

  ; add one number to indx
  inc ecx
  ; if value != 0 { ends loop }
  cmp DWORD [write], 0
  jne convert_loop

  ; add number of algarisms to the last position of the stack
  mov [esp + 12], ecx

invert_output:
  dec ecx

  ; zero eax to make swap
  sub eax, eax
  sub edx, edx
  sub ebx, ebx
invert_loop:
  cmp ecx, 0
  je break

  mov bl, [esp + eax]
  mov dl, [esp + ecx]
  mov [esp + eax], dl
  mov [esp + ecx], bl


  inc eax
  dec ecx

  cmp eax, ecx
  jl invert_loop


break:
  mov eax, 4
  mov ebx, 1
  mov ecx, esp
  mov edx, 12
  int 80h

  add esp, 12

  mov eax, 1
  mov ebx, 0
  int 80h
