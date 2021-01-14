list:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_list list.c integer.c p3_e2.c
run_list:
	valgrind --leak-check=full --track-origins=yes ./exe_list 10
