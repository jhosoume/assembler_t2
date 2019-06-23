section .data
  write DD 22

section .text
extern WriteInteger
extern ReadInteger

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

  call ReadInteger
  ; push DWORD [write]
  ; shl eax, 1
  mov ebx, 2
  imul eax, ebx
  push eax
  call WriteInteger
  pop eax

  ; call ReadInteger
  ; ; push DWORD [write]
  ; shl eax, 1
  ; push eax
  ; call WriteInteger
  ; pop eax

  mov eax, 1
  mov ebx, 0
  int 80h
