CC=gcc
CFLAGS = -g
OBJECTS= y.tab.o lex.yy.o

.PHONY: pruebaSintactico clean all

all: clean alfay alfa $(OBJECTS) pruebaSintactico

pruebaSintactico:
	gcc -o pruebaSintactico pruebaSintactico.c $(OBJECTS)
	
alfay: alfa.y
	bison -d -y -v alfa.y

alfa: alfa.l
	flex alfa.l

lex.yy.o: lex.yy.c 
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.h y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c
  
clean:
	rm -rf *.o pruebaSintactico lex.yy.c y.tab.c y.tab.h y.output *.txt
