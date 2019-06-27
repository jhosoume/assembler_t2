global _start
 section .text
 _start: 
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
 
 ;-----------------------------------------------------
 ; Procedure that reads a char from the keyboard
 ; The value read is return in the eax!
 ; nasm -f elf -o ReadChar.o ReadChar.s
 ;
 ;-----------------------------------------------------
 
 ; %define CHAR_ADDR DWORD [ebp + 8]
 
 global ReadChar
 
 ReadChar:
     ; save read in the stack
     ; 12 = 10 digits + 1 sign + 1 size
     enter 0, 0
 
     ; get char
     mov eax, 3
     mov ebx, 0
     mov ecx, [ebp + 8]
     mov edx, 1
     int 80h
 
     leave
     ret
 
 
 ;-----------------------------------------------------
 ; Procedure that write a char in the screen from number in stack
 ; The value read is return in the eax!
 ; nasm -f elf -o WriteChar.o WriteChar.s
 ;
 ;-----------------------------------------------------
 
 %define CHAR_ADDR DWORD [ebp + 8]
 
 global WriteChar
 
 WriteChar:
     enter 0, 0
 
     ; write char
     mov eax, 4
     mov ebx, 1
     mov ecx, CHAR_ADDR
     mov edx, 1
     int 80h
 
     leave
     ret
 
 
 ;-----------------------------------------------------
 ; Procedure that reads an integer from the keyboard
 ; The value read is return in the eax!
 ; nasm -f elf -o ReadInteger.o ReadInteger.s
 ;
 ;-----------------------------------------------------
 
 ; %define INPUT_SIZE DWORD [esp + 11]
 ; %define INPUT_ADDR DWORD [ebp + 8]
 
 global ReadIntegerAddr
 
 ReadIntegerAddr:
     ; save read in the stack
     ; 12 = 10 digits + 1 sign + 1 size
     enter 12, 0
 
     ; zero stack positions
     mov ecx, 12
   zeroing_loopRI:
     mov BYTE [esp + ecx], 0
     loop zeroing_loopRI
 
     ; zero flag
     mov edi, 0
 
     ; get all numbers
     mov eax, 3
     mov ebx, 0
     mov ecx, esp
     mov edx, 11
     int 80h
 
     ; save numbers read
     mov [esp + 11], eax
 
     ; check if last is a new line
   check_last_new_lineRI:
     ; get pointer to the last character read
     mov esi, esp
     add esi, [esp + 11]
     dec esi
 
     ; make comparision to new line ascii
     cmp BYTE [esi], 0xA
     ; jump to next comparision if it isnt a new line
     jne check_minus_symbolRI
 
   deal_new_lineRI:
     ; remove new line
     dec BYTE [esp + 11]
 
   check_minus_symbolRI:
     ; check if first byte is a minus sign
     cmp BYTE [esp], 0x2D
     jne deal_positive_signRI
 
     ; if it has a minus sign, set flag
     mov edi, 1
 
   deal_negative_signRI:
     mov ecx, 1
     jmp do_conversionRI
 
   deal_positive_signRI:
     mov ecx, 0
     jmp do_conversionRI
 
   do_conversionRI:
     ; zero acumulator
     mov eax, 0
   do_conversion_loopRI:
     ; check if all characters were dealt with
     cmp ecx, [esp + 11]
     jge should_negRI
 
     ; multiply old value by ten
     mov edx, eax
     shl eax, 3
     add eax, edx
     add eax, edx
 
     sub ebx, ebx
     ; get character in ebx
     mov BYTE bl, [esp + ecx]
     sub BYTE bl, 0x30
 
     ; add new number to old result
     add eax, ebx
 
     ; ++indx
     inc ecx
     jmp do_conversion_loopRI
 
   ; if flag was set, needs to change to negative
   should_negRI:
     cmp edi, 1
     jne end_convRI
 
   ; if number is negative, convert
   convert_negRI:
     not eax
     inc eax
 
   end_convRI:
     mov esi, [ebp + 8]
     mov [esi], eax
     mov eax, [esp + 11]
     ; print numbers just to check
     ; mov edi, esp
     ; add edi, 2
     ; mov eax, 4
     ; mov ebx, 1
     ; mov ecx, edi
     ; mov edx, 1
     ; int 80h
 
     ; mov eax, [esp + 11]
 
   breakRI:
     leave
     ret
 
 
 ;-----------------------------------------------------
 ; Procedure that receives an integer from the stack
 ; (last stacked double word) then prints it.
 ; nasm -f elf -o WriteInteger.o WriteInteger.s
 ;-----------------------------------------------------
 
 ; %define INPUT_ADDR DWORD [ebp + 8]
 
 global WriteIntegerAddr
 
 WriteIntegerAddr:
     ; save result in the stack
     ; 12 = 10 digits + 1 sign + 1 size
     enter 12, 0
 
     ; zero stack positions
     mov ecx, 12
   zeroing_loopWI:
     mov BYTE [esp + ecx], 0
     loop zeroing_loopWI
 
     ; zero flag
     mov edi, 0
 
     mov esi, [ebp + 8]
     mov esi, [esi]
   check_negativeWI:
     cmp esi, 0
     jl deal_negativeWI
 
   deal_positiveWI:
     jmp main_writeWI
 
   deal_negativeWI:
     ; set flag indicating that number needs the minus
     mov edi, 1
     ; transform negative
     not esi
     inc esi
 
   main_writeWI:
     ; Zero Index, ECX = indx
     ; Value = Write
     sub ecx, ecx
   convert_loopWI:
     ; Gets value divided by ten
     ; Dividend
     mov eax, esi
     cdq
     ; Divisor
     mov ebx, 10
     ; eax will have the quotient
     ; edx will have the rest
     idiv ebx
 
     ;output [indx] = (char) ((value % 30) + 0x30)
     add BYTE dl, 0x30
     mov BYTE [esp + ecx], dl
 
     ;value = value/10
     mov esi, eax
 
     ; add one number to indx
     inc ecx
     ; if value != 0 { ends loop }
     cmp esi, 0
     jne convert_loopWI
 
     ; add number of algarisms (size) to the last position of the stack
     mov [esp + 12], ecx
 
   check_minusWI:
     ; check if needs minus sign
     cmp edi, 1
     jne invert_outputWI
     ; get indx of last character
     mov ecx, [esp + 12]
     ; adding the minus sign
     mov BYTE [esp + ecx], 0x2D
     ; increments the total size
     inc BYTE [esp + 12]
 
   invert_outputWI:
     ; Size is turned into indx, indx = size - 1
     mov ecx, [esp + 12]
     dec ecx
 
     ; eax is the other indx
     sub eax, eax
     ; dl and bl are used to make swap
     sub edx, edx
     sub ebx, ebx
   invert_loopWI:
     ; if the number has size 0, stop
     cmp ecx, 0
     je end_and_printWI
 
     ; swaping positions
     mov bl, [esp + eax]
     mov dl, [esp + ecx]
     mov [esp + eax], dl
     mov [esp + ecx], bl
 
     ; move indexes
     inc eax
     dec ecx
 
     ; when indexes cross each other, stop
     cmp eax, ecx
     jl invert_loopWI
 
   end_and_printWI:
     ; write result in the screen
     mov eax, 4
     mov ebx, 1
     mov ecx, esp
     mov edx, 12
     int 80h
 
   breakWI:
     leave
     ret
 
 section .data
 AUX:
 DD 0
 N:
 DD 0
 ONE:
 DD 1
 