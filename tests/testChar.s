global _start
 section .text
 _start: 
 push eax
 call ReadChar
 mov [C], eax
 pop eax
 push eax
 push DWORD S
 push DWORD 100
 call ReadString
 pop edx
 pop edx
 pop eax
 mov edx, [C]
 mov [S + 1], edx
 push DWORD C
 call WriteChar
 pop edx
 push eax
 push DWORD S
 push DWORD 100
 call WriteString
 pop edx
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 C:
 DD 0
 S:
 DD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 