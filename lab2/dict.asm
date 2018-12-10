
extern string_equals
extern string_length


section .text

find_word:
    .loop:
        add rsi, 8 ; get key ptr
        push rdi
        push rsi
        call string_equals
        pop rsi
        pop rdi
        test rax, rax
        jnz .find_exit
        sub rsi, 8 ; get ptr to next word
        cmp qword[rsi], 0
        jz .not_find_exit
        mov rsi, qword[rsi]
        jmp .loop
    .find_exit:
        push rsi
        call string_length
        pop rsi
        add rax, rsi ; calcualte record address
        inc rax
        ret
    .not_find_exit:
        xor rax, rax
        ret
        
