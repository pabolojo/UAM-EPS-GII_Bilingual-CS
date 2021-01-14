CC=gcc
CFLAGS = -g
OBJECTS= hashTable.o symbolTable.o

.PHONY: prueba_tabla clean all

all: clean prueba_tabla

prueba_tabla: alfa $(OBJECTS)
	gcc -o prueba_tabla lex.yy.c $(OBJECTS)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

alfa: alfa.l
	flex alfa.l
  
clean:
	rm -rf *.o prueba_tabla testOutput.txt lex.yy.c
