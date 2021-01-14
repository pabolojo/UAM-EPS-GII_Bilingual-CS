all:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e4 p2_e4.c stack_fc.c graph.c node.c

run_e4_archivo:
	valgrind --leak-check=full --track-origins=yes ./exe_e4 archivo 1 5
