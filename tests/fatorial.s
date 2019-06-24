extern WriteIntegerAddr
extern ReadIntegerAddr

global main
 section .text
 main:
 push eax
 push DWORD N
 call ReadIntegerAddr
 pop edx
 pop eax
 mov eax, [N]
 FAT:
 sub eax, [ONE]
 cmp eax, 0
 je FIM
 mov [AUX], eax
 mov ebx, [N]
 imul eax, ebx
 mov [N], eax
 mov eax, [AUX]
 jmp FAT
 FIM:
 push eax
 push DWORD N
 call WriteIntegerAddr
 pop edx
 pop eax
 mov eax, 1
 mov ebx, 0
 int 80h
 section .data
 AUX:
 DD 0
 N:
 DD 0
 ONE:
 DD 1
