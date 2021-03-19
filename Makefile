stack:
	gcc -c stack.c
assembler:
	gcc -o assembler assembler.cpp
	./assembler commands.txt
CPU:
	gcc -c CPU.c
	gcc -o CPU stack.o CPU.o
disassemble:
	gcc -o dis_asm dis_asm.cpp
	./dis_asm commands_codes.txt 
develop:
	gcc -o make make.cpp