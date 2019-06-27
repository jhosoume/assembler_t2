global _start
 section .text
 _start: 
 push eax
 push DWORD N1 + 3
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N2
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [N1 + 3]
 add eax, [N2]
 mov [N1 + 3], eax
 push eax
 push DWORD N1 + 3
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD N3 + 4
 push DWORD 40
 call ReadString
 pop edx
 pop edx
 pop eax
 push eax
 push DWORD N3 + 4
 push DWORD 40
 call WriteString
 pop edx
 pop edx
 pop eax
 push eax
 call ReadChar
 mov [N4 + 3], eax
 pop eax
 push DWORD N4 + 3
 call WriteChar
 pop edx
 mov eax, [N5 + 2]
 add eax, [N6 + 3]
 mov [N5 + 2], eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 N1:
 DD 0, 0, 0, 0, 0
 N2:
 DD 0, 0, 0, 0, 0
 N3:
 DD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 N4:
 DD 0, 0, 0, 0, 0
 N5:
 DD 0, 0, 0, 0, 0
 N6:
 DD 0, 0, 0, 0, 0
 