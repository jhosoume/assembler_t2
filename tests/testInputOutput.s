global _start
 section .text
 _start: 
 push eax
 push DWORD N1 + 5
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N2
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [N2]
 mov ebx, [N1 + 5]
 imul eax, ebx
 mov [N2], eax
 push eax
 push DWORD N2
 call WriteIntegerAddr
 pop edx
 pop eax
 mov ebx, [N1 + 5]
 cdq
 idiv ebx
 mov [N2], eax
 push eax
 push DWORD N2
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 N1:
 DD 0, 0, 0, 0, 0, 0
 N2:
 DD 0
 