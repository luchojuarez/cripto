nasm -f elf32 sub.asm
gcc -o main.app -m32 sub.o asm_io.o main.c
./main.app
