global _start
 section .text
 _start: 
 push eax
 push DWORD INIT
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD POSITIVE
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NEGATIVE
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NEUTRAL
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD VECTOR
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD VECTOR + 4
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD VECTOR + 8
 call ReadIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD NEUTRAL
 call WriteIntegerAddr
 pop edx
 pop eax
 jmp INITIAL_LABEL
 MA_LABEL:
 push eax
 push DWORD NEGATIVE
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, [NEGATIVE]
 mov ebx, [TEN]
 imul eax, ebx
 mov ebx, [FIVE]
 cdq
 idiv ebx
 mov [NEGATIVE], eax
 push eax
 push DWORD NEGATIVE
 call WriteIntegerAddr
 pop edx
 pop eax
 mov edx, [NEGATIVE]
 mov [VECTOR + 4], edx
 jmp FINAL_LABEL
 BOA_LABEL:
 push eax
 push DWORD POSITIVE
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, [POSITIVE]
 mov ebx, [TEN]
 imul eax, ebx
 mov ebx, [FIVE]
 cdq
 idiv ebx
 mov [POSITIVE], eax
 push eax
 push DWORD POSITIVE
 call WriteIntegerAddr
 pop edx
 pop eax
 mov edx, [POSITIVE]
 mov [VECTOR + 4], edx
 jmp FINAL_LABEL
 NEUTRAL_LABEL:
 push eax
 push DWORD NEUTRAL
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, [NEUTRAL]
 mov ebx, [TEN]
 imul eax, ebx
 mov ebx, [FIVE]
 cdq
 idiv ebx
 mov [NEUTRAL], eax
 push eax
 push DWORD NEUTRAL
 call WriteIntegerAddr
 pop edx
 pop eax
 mov edx, [NEUTRAL]
 mov [VECTOR + 4], edx
 jmp FINAL_LABEL
 INITIAL_LABEL:
 push eax
 push DWORD INIT
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, [INIT]
 cmp eax, 0
 jg BOA_LABEL
 cmp eax, 0
 jl MA_LABEL
 cmp eax, 0
 je NEUTRAL_LABEL
 FINAL_LABEL:
 push eax
 push DWORD VECTOR
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD VECTOR + 4
 call WriteIntegerAddr
 pop edx
 pop eax
 push eax
 push DWORD VECTOR + 8
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 INIT:
 DD 0
 POSITIVE:
 DD 0
 NEGATIVE:
 DD 0
 NEUTRAL:
 DD 0
 VECTOR:
 DD 0, 0, 0
 TEN:
 DD 40
 5:
 DD FIVE
 C:
 DD 0
 S:
 DD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 