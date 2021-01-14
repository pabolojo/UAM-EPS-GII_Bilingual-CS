.PHONY: pruebaMorfo clean all alfa

all: clean pruebaMorfo

pruebaMorfo: alfa
	gcc -Wall -o pruebaMorfo lex.yy.c

alfa: alfa.l
	flex alfa.l

clean:
	rm -rf *.o lex.yy.c pruebaMorfo alfa