;-----------------------------------------------------
; Procedure that receives an integer from the stack
; (last stacked double word) then prints it.
; nasm -f elf -o WriteInteger.o WriteInteger.s
;-----------------------------------------------------

%define INPUT_ADDR DWORD [ebp + 8]

global WriteIntegerAddr

WriteIntegerAddr:
    ; save result in the stack
    ; 12 = 10 digits + 1 sign + 1 size
    enter 12, 0

    ; zero stack positions
    mov ecx, 12
  zeroing_loop:
    mov BYTE [esp + ecx], 0
    loop zeroing_loop

    ; zero flag
    mov edi, 0

    mov esi, INPUT_ADDR
    mov esi, [esi]
  check_negative:
    cmp esi, 0
    jl deal_negative

  deal_positive:
    jmp main_write

  deal_negative:
    ; set flag indicating that number needs the minus
    mov edi, 1
    ; transform negative
    not esi
    inc esi

  main_write:
    ; Zero Index, ECX = indx
    ; Value = Write
    sub ecx, ecx
  convert_loop:
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
    jne convert_loop

    ; add number of algarisms (size) to the last position of the stack
    mov [esp + 12], ecx

  check_minus:
    ; check if needs minus sign
    cmp edi, 1
    jne invert_output
    ; get indx of last character
    mov ecx, [esp + 12]
    ; adding the minus sign
    mov BYTE [esp + ecx], 0x2D
    ; increments the total size
    inc BYTE [esp + 12]

  invert_output:
    ; Size is turned into indx, indx = size - 1
    mov ecx, [esp + 12]
    dec ecx

    ; eax is the other indx
    sub eax, eax
    ; dl and bl are used to make swap
    sub edx, edx
    sub ebx, ebx
  invert_loop:
    ; if the number has size 0, stop
    cmp ecx, 0
    je end_and_print

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
    jl invert_loop

  end_and_print:
    ; write result in the screen
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, 12
    int 80h

  break:
    leave
    ret
