global _start
 section .text
 _start: 
 push eax
 push DWORD B
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD H
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [B]
 mov ebx, [H]
 imul eax, ebx
 mov ebx, [DOIS]
 cdq
 idiv ebx
 mov [R], eax
 push eax
 push DWORD R
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 B:
 DD 0
 H:
 DD 0
 R:
 DD 0
 DOIS:
 DD 2
 