all:
	gcc -c -Wall -pedantic table.c main.c index.c cmds.c import.c type.c
	gcc -o a main.o table.o type.o cmds.o import.o index.o
run:
	valgrind --leak-check=full --track-origins=yes --tool=memcheck ./a 2 INT STR
