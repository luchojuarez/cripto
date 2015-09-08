gcc -o main.app -m32 sub.o asm_io.o main.c
-f elf32 sub.asm
./main.app
