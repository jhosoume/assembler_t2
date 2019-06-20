;-----------------------------------------------------
; Procedure that reads an integer from the keyboard
; The value read is return in the eax!
; nasm -f elf -o ReadInteger.o ReadInteger.s
;
;-----------------------------------------------------

%define INPUT_SIZE   DWORD [esp + 11]

global ReadInteger

ReadInteger:
    ; save read in the stack
    ; 12 = 10 digits + 1 sign + 1 size
    enter 12, 0

    ; zero stack positions
    mov ecx, 12
  zeroing_loop:
    mov BYTE [esp + ecx], 0
    loop zeroing_loop

    ; zero flag
    mov edi, 0

    ; get all numbers
    mov eax, 3
    mov ebx, 0
    mov ecx, esp
    mov edx, 11
    int 80h

    ; save numbers read
    mov INPUT_SIZE, eax

    ; check if last is a new line
  check_last_new_line:
    ; get pointer to the last character read
    mov esi, esp
    add esi, INPUT_SIZE
    dec esi

    ; make comparision to new line ascii
    cmp BYTE [esi], 0xA
    ; jump to next comparision if it isnt a new line
    jne check_minus_symbol

  deal_new_line:
    ; remove new line
    dec BYTE INPUT_SIZE

  check_minus_symbol:
    ; check if first byte is a minus sign
    cmp BYTE [esp], 0x2D
    jne deal_positive_sign

    ; if it has a minus sign, set flag
    mov edi, 1
  deal_negative_sign:
    mov ecx, 1
    jmp do_conversion

  deal_positive_sign:
    mov ecx, 0
    jmp do_conversion

  do_conversion:
    cmp ecx, INPUT_SIZE
    jge end_conv



  end_conv:
    ; print numbers just to see
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, INPUT_SIZE
    int 80h

    ; mov eax, INPUT_SIZE

  break:
    leave
    ret
