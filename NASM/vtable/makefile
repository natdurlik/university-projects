out: main.cpp 13_1.asm
	   g++ -no-pie -fno-devirtualize -c main.cpp -o main.o
	   nasm -felf64 change.asm -o change.o
	   g++ -no-pie -fno-devirtualize main.o change.o -o main

