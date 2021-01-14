CC=gcc
CFLAGS = -g 
OBJECTS= y.tab.o lex.yy.o symbolTable.o hashTable.o generacion.o

.PHONY: alfa clean all

all: clean alfal alfay $(OBJECTS) alfa

alfa: $(OBJECTS)
	$(CC) $(CFLAGS) -o alfa alfa.c $(OBJECTS)
	
alfay: alfa.y
	bison -d -y -v alfa.y

alfal: alfa.l
	flex alfa.l

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.h y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c
	
generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c

hashTable.o: hashTable.c hashTable.h
	$(CC) $(CFLAGS) -c hashTable.c

symbolTable.o: symbolTable.c symbolTable.h
	$(CC) $(CFLAGS) -c symbolTable.c
  
clean:
	rm -rf $(OBJECTS) pruebaSintactico lex.yy.c y.tab.c y.tab.h y.output *.txt alfa
