# Makefile 

CC = gcc
FLAGS = -Wall -ansi
EXS = example1 example2 example3 example4 example5 example6 example7
OBJ = example1.o example2.o example3.o example4.o example5.o example6.o example7.o generacion.o

.phony: clean all

all: clean generacion.o $(EXS)

$(EXS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< generacion.o

example1.o: example1.c generacion.h 
	$(CC) $(CFLAGS) -c example1.c
	
example2.o: example2.c generacion.h
	$(CC) $(CFLAGS) -c example2.c
	
example3.o: example3.c generacion.h
	$(CC) $(CFLAGS) -c example3.c
	
example4.o: example4.c generacion.h
	$(CC) $(CFLAGS) -c example4.c

example5.o: example5.c generacion.h
	$(CC) $(CFLAGS) -c example5.c

example6.o: example6.c generacion.h
	$(CC) $(CFLAGS) -c example6.c

example7.o: example7.c generacion.h
	$(CC) $(CFLAGS) -c example7.c

generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c

ex1:
	nasm -g -o ex1.o -f elf32 ex1.asm
	gcc -m32 -o ex1 ex1.o alfalib.o

ex2:
	nasm -g -o ex2.o -f elf32 ex2.asm
	gcc -m32 -o ex2 ex2.o alfalib.o

ex3:
	nasm -g -o ex3.o -f elf32 ex3.asm
	gcc -m32 -o ex3 ex3.o alfalib.o

ex4:
	nasm -g -o ex4.o -f elf32 ex4.asm
	gcc -m32 -o ex4 ex4.o alfalib.o

ex5:
	nasm -g -o ex5.o -f elf32 ex5.asm
	gcc -m32 -o ex5 ex5.o alfalib.o

ex6:
	nasm -g -o ex6.o -f elf32 ex6.asm
	gcc -m32 -o ex6 ex6.o alfalib.o

ex7:
	nasm -g -o ex7.o -f elf32 ex7.asm
	gcc -m32 -o ex7 ex7.o alfalib.o

clean:
	rm -rf $(EXS) $(OBJ) 
