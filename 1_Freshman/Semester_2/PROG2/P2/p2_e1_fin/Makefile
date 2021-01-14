all:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e1 p2_e1.c elestack.c node.c stack_elestack.c

run_e1:
	valgrind --leak-check=full --track-origins=yes ./exe_e1
