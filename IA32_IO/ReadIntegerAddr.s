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
