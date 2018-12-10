%include "colon.inc"

section .data
%include "words.inc"
input_buffer: times 256 db 0
msg_noword: db "No such word", 0
key: db "kono", 0

section .text

global _start

extern find_word
extern print_string
extern print_error
extern print_newline
extern read_word
extern exit

_start:
    mov rdi, input_buffer
    mov rsi, 256
    call read_word
    mov rdi, rax
    mov rsi, lastPtr
    call find_word
    test rax, rax
    jz .error_msg
    mov rdi, rax
    call print_string
    jmp .exit
    .error_msg:
        mov rdi, msg_noword
        call print_error
    .exit:
        call print_newline
        call exit
