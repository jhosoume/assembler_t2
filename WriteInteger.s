%define INPUT_INT DWORD [ebp + 8]

global WriteInteger

WriteInteger:
    ; save result in the stack
    enter 12, 0

    ; zero stack positions
    mov ecx, 12
  zeroing_loop:
    mov BYTE [esp + ecx], 0
    loop zeroing_loop

  check_negative:
    cmp DWORD INPUT_INT, 0
    jl deal_negative

  deal_positive:
    jmp WriteInteger

  deal_negative:
    ; set flag indicating that number needs the minus
    mov edi, 1
    not DWORD INPUT_INT
    inc DWORD INPUT_INT

  main_write:
    ; Zero Index, ECX = indx
    ; Value = Write
    sub ecx, ecx
  convert_loop:
    ; Gets value divided by ten
    ; Dividend
    mov eax, INPUT_INT
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
    mov INPUT_INT, eax

    ; add one number to indx
    inc ecx
    ; if value != 0 { ends loop }
    cmp DWORD INPUT_INT, 0
    jne convert_loop

    ; add number of algarisms (size) to the last position of the stack
    mov [esp + 12], ecx

  check_minus:
    ; check if needs minus sign
    cmp edi, 1
    jne invert_output
    mov ecx, [esp + 12]
    mov BYTE [esp + ecx], 0x2D
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
