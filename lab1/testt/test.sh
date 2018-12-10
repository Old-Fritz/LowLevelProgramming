#!/bin/bash
nasm -g -felf64 test.asm -o test.o
ld -o test test.o
chmod u+x test
./test
