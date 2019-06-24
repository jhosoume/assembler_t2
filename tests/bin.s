extern WriteIntegerAddr
extern ReadIntegerAddr

global main
 section .text
 main:
 push eax
 push DWORD OLD_DATA
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [OLD_DATA]
 L1:
 mov ebx, [DOIS]
 cdq
 idiv ebx
 mov [NEW_DATA], eax
 mov ebx, [DOIS]
 imul eax, ebx
 mov [TMP_DATA], eax
 mov eax, [OLD_DATA]
 sub eax, [TMP_DATA]
 mov [TMP_DATA], eax
 push eax
 push DWORD TMP_DATA
 call WriteIntegerAddr
 pop edx
 pop eax
 mov edx, [NEW_DATA]
 mov [OLD_DATA], edx
 mov eax, [OLD_DATA]
 cmp eax, 0
 jg L1
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 DOIS:
 DD 2
 OLD_DATA:
 DD 0
 NEW_DATA:
 DD 0
 TMP_DATA:
 DD 0
