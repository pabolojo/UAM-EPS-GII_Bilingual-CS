all:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e2 p2_e3-int.c int.c stack_fc.c
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e1 p2_e3-node.c node.c stack_fc.c

run_e1:
	valgrind --leak-check=full --track-origins=yes ./exe_e1

run_e2:
	valgrind --leak-check=full --track-origins=yes ./exe_e2 10
