section .data
  write DD -00123

section .text
extern WriteInteger

global main
main:
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

  push DWORD [write]
  call WriteInteger
  pop DWORD [write]

  mov eax, 1
  mov ebx, 0
  int 80h
