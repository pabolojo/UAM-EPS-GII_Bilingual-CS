all:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e2 p2_e2.c elestack-int.c stack_elestack.c

run_e2:
	valgrind --leak-check=full --track-origins=yes ./exe_e2 10
