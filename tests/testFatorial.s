global _start
 section .text
 _start: 
 push eax
 push DWORD NUM
 call ReadIntegerAddr
 pop edx
 pop eax
 mov edx, [1]
 mov [RESULT], edx
 mov edx, [1]
 mov [I], edx
 LOOP:
 mov eax, [I]
 sub eax, [NUM]
 cmp eax, 0
 jg FIM
 mov eax, [RESULT]
 mov ebx, [I]
 imul eax, ebx
 mov [RESULT], eax
 mov eax, [I]
 add eax, [1]
 mov [I], eax
 jmp LOOP
 FIM:
 push eax
 push DWORD RESULT
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 RESULT:
 DD 0
 I:
 DD 0
 NUM:
 DD 0
 