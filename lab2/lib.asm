section .text
global string_length
global print_string
global print_error
global print_char
global print_newline
global exit
global print_uint
global print_int
global read_char
global read_word
global parse_uint
global parse_int
global string_equals
global string_copy


string_length:
xor rax, rax
.begin:
cmp byte [rdi+rax], 0
jz .end
inc rax
jmp .begin
.end:
ret


print_string:
push rdi
call string_length
pop rsi
mov rdx, rax
mov rax, 1
mov rdi, 1
syscall
ret

print_error:
push rdi
call string_length
pop rsi
mov rdx, rax
mov rax, 1
mov rdi, 2
syscall
ret

print_char:
push rdi
mov rsi, rsp
mov rax, 1
mov rdi, 1
mov rdx, 1
syscall
pop rdi
ret

print_newline:
mov rdi, 0xA
call print_char
ret

exit:
mov rax, 60
xor rdi, rdi
syscall

print_uint:
mov rax, rdi
mov r8, 10
push rbp
mov rbp, rsp
sub rsp, 20
mov byte[rsp], 0
.loop:
xor rdx, rdx
dec rsp
div r8
add rdx, 0x30
mov byte[rsp], dl
test rax, rax
jne .loop
mov rdi, rsp
call print_string
mov rsp, rbp
pop rbp
ret


print_int:
test rdi, rdi
jns print_uint
neg rdi
push rdi
mov rdi, '-'
call print_char
pop rdi
call print_uint      
ret



read_char:
push 0
mov rdx, 1
mov rax, 0
mov rdi, 0
mov rsi, rsp
syscall
pop rax
ret 

read_word:
xor r8, r8
push rdi
mov r10, rdi
mov r9, rsi
.begin:
call read_char
test rax, rax
jz .end
cmp rax, 0x0A
jz .end
cmp rax, 0x20
jle .begin


.read:
inc r8
cmp r8, r9
jg .error
mov [r10], rax
inc r10
call read_char
cmp rax, 0x20
jle .end
jmp .read
.end:
mov byte[r10], 0
mov rdx, r8
pop rax
ret
.error:
pop rax
xor rax, rax
ret

parse_uint:
    mov r8, 10
    xor rcx, rcx
    xor rax, rax
    .loop:
    mov r9b, byte[rdi+rcx]
    cmp r9b, '0'
    jb .end
    cmp r9b, '9'
    ja .end
    sub r9b, '0'
    mul r8
    add al, r9b
    inc rcx
    jmp .loop
    .end:
    mov rdx, rcx
    ret

parse_int:
    mov al, byte[rdi]
    cmp al, '-'
    jz .sign
    jmp parse_uint
    .sign:
    inc rdi
    call parse_uint
    neg rax
    inc rdx
    ret 

string_equals:
    xor rcx, rcx
.loop:
    mov al, byte[rdi+rcx]
    cmp al, byte[rsi+rcx]
    jnz .end
    inc rcx
    test al, al
    jnz .loop
    mov rax, 1
    ret
    .end:
    xor rax, rax
    ret
    
    
    

string_copy:
push rdi 
push rsi
push rdx
call string_length
pop rdx
pop rsi
pop rdi
cmp rax, rdx
jae .error
xor rcx, rcx
.loop:
mov dl, byte[rdi+rcx]
mov byte[rsi+rcx], dl
inc rcx
test dl, dl
jne .loop
mov rax, rsi
ret
.error:
xor rax, rax
ret

