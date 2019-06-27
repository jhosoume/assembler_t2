global _start
 section .text
 _start: 
 push eax
 push DWORD NUM
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NUM + 1
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NUM + 2
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [NUM]
 mov ebx, [NUM + 1]
 cdq
 idiv ebx
 mov ebx, [NUM + 2]
 cdq
 idiv ebx
 mov [RESULT], eax
 push eax
 push DWORD RESULT
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NUM
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NUM + 1
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NUM + 2
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section  NUM:
 DD 0, 0, 0
 RESULT:
 DD 0
 