global _start
 section .text
 _start: 
 push eax
 push DWORD A
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [A]
 mov [B], edx
 push eax
 push DWORD B
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 B:
 DD 0
 A:
 DD 0
 C:
 DD 0
 D:
 DD 0
 DOIS:
 DD 2
 