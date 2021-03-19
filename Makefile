stack:
	gcc -c stack.c
assembler:
	gcc -o assembler assembler.cpp
CPU:
	gcc -c CPU.c
	gcc -o CPU stack.o CPU.o
develop:
	gcc -o make make.cpp