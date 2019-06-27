global _start
 section .text
 _start: 
 push eax
 push DWORD N
 push DWORD N
 call ReadString
 pop edx
 pop edx
 pop eax
 push eax
 push DWORD N
 push DWORD N
 call WriteString
 pop edx
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 N:
 DD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 