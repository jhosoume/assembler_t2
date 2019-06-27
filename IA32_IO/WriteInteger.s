;-----------------------------------------------------
; Procedure that receives an integer from the stack
; (last stacked double word) then prints it.
; nasm -f elf -o WriteInteger.o WriteInteger.s
;-----------------------------------------------------

; %define INPUT_INT DWORD [ebp + 8]

global WriteInteger

WriteInteger:
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

  check_negativeWI:
    cmp DWORD [ebp + 8], 0
    jl deal_negative

  deal_positiveWI:
    jmp main_writeWI

  deal_negativeWI:
    ; set flag indicating that number needs the minus
    mov edi, 1
    ; transform negative
    not DWORD [ebp + 8]
    inc DWORD [ebp + 8]

  main_writeWI:
    ; Zero Index, ECX = indx
    ; Value = Write
    sub ecx, ecx
  convert_loopWI:
    ; Gets value divided by ten
    ; Dividend
    mov eax, [ebp + 8]
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
    mov [ebp + 8], eax

    ; add one number to indx
    inc ecx
    ; if value != 0 { ends loop }
    cmp DWORD [ebp + 8], 0
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
