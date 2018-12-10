global _start

section .data
message1: db ' ',0
message2: db '',0
word_buffer : times 255 db 0

section .text

%define ASCII_H_F 0x21 ; first readable ASCII symbol's code 
%define ASCII_N_F 0x30 ; first ASCII number symbol's code
%define ASCII_N_L 0x39 ; last  ASCII number symbol's code

exit:
    mov rax, 60
    syscall

string_length:
    mov rax, -1
    .loop:
        inc rax
        cmp byte[rdi + rax], 0
        jnz .loop
    ret

print_string:
    call string_length
    mov rdx, rax
    mov rsi, rdi
    mov rax, 1   
    mov rdi, 1
    syscall
    ret

print_char:
    push rdi
	mov rsi, rsp
	mov rdx,1
	mov rax,1
	mov rdi,1
	syscall
    pop rdi
    ret

print_newline:
    mov dil, 0xA
    jmp print_char

print_int:
    cmp rdi, 0
    jnl print_uint
    xor rdi, -1
    inc rdi
    mov r8, rdi
    mov rdi, '-'
    call print_char
    mov rdi, r8

print_uint:
    mov rax, rdi
    xor rdx, rdx
    mov r8, 10
    mov dil, '0'
    mov rcx, rsp
    dec rcx
    sub rsp, 64
    mov byte[rcx], 0
    .loop:
        dec rcx
        div r8
        add dl, '0'
        mov byte[rcx], dl
        xor rdx, rdx
        cmp rax, 0
        jnz .loop
    mov rdi, rcx
    call print_string
    add rsp, 64
    ret

read_char:
    xor rax, rax
    sub rsp, 1
    mov rsi, rsp
    mov rdx,1
	mov rax,0
	mov rdi,0
    syscall
    cmp al, 0
    jz .exit
    mov al, byte[rsi]
    .exit:
        add rsp, 1
        ret

read_word:
    mov r8, rdi ; save current buffer ptr
    xor r9, r9  ; size of buffer
    add r10, rsi ; save max size
    
    .skip:
        call read_char
        cmp al, 0
        jz .exit
        cmp al, 0x21
        jl .skip
    jmp .write_char
    .loop:
        call read_char
        cmp al, 0x21
        jl .norm_exit
    .write_char:
        mov byte[r8 + r9], al  ; first symbol
        inc r9
        cmp r9, r10 ; check end of buffer
        jnz .loop
        xor rax, rax ; 0 return code
        dec r9
        jmp .exit
    .norm_exit:
        mov rax, r8 ; 1 return code
    .exit:
        mov byte[r8 + r9], 0 ; write 0 end code
        mov rdx, r9
        ret

parse_uint:
    xor rax, rax
    mov rcx, 0 ; size of number
    xor rsi, rsi
    mov r8, 10 
    .loop:
        mov sil, byte[rdi + rcx]
        cmp sil, '0'
        jl .exit
        cmp sil, '9'
        jg .exit
        sub sil, '0'
        mul r8
        add rax, rsi
        
        inc rcx
        jmp .loop
    .exit:
        mov rdx, rcx
        inc rcx
        ret
        
parse_int:
    mov sil, byte[rdi]
    cmp sil, '-'
    jz .negative
    call parse_uint
    jmp .exit
    .negative:
        inc rdi
        call parse_uint
        test rax, rax
        jz .exit
        inc rdx
        xor rax, -1
        inc rax
    .exit:
        ret

string_equals:
    xor rax, rax
    .loop:
        mov dl, byte[rdi]
        cmp dl, byte[rsi]
        jnz .exit
        inc rdi
        inc rsi
        test dl, dl
        jnz .loop
        mov rax, 1
    .exit:
        ret

string_copy:
    xor rax, rax
    xor rcx, rcx
    mov r8, rdx
    .loop:
        cmp r8, rcx
        jle .exit
        mov dl, byte[rdi + rcx]
        mov byte[rsi + rcx], dl
        test dl, dl
        jz .dest_exit
        inc rcx
        jmp .loop
    .dest_exit:
        mov rax, rsi
    .exit:
        ret
    
_start:
    mov rcx, rcx
    .exit:
        call exit
