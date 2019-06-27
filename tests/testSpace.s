global _start
 section .text
 _start: 
 push eax
 push DWORD N1 + 1
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [N1 + 1]
 mov [N2], edx
 push eax
 push DWORD N4
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [N4]
 mov [N3 + 3], edx
 push eax
 push DWORD N5 + 1
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [N5 + 1]
 mov [N6 + 3], edx
 push eax
 push DWORD N7
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [N7]
 mov [N8], edx
 push eax
 push DWORD N2
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N3 + 3
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N6 + 3
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N8
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 N1:
 DD 0, 0
 N2:
 DD 0
 N3:
 DD 0, 0, 0, 0
 N4:
 DD 0
 N5:
 DD 0, 0
 N6:
 DD 0, 0, 0, 0
 N7:
 DD 0
 N8:
 DD 0
 