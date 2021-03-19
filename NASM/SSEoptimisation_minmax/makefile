out: main.cpp 10_1.asm
	nasm -f elf32 minmax.asm -o minmax.o
	g++ -no-pie -w -c main.cpp -m32 -o main.o
	g++ -no-pie -m32 minmax.o main.o -o main

