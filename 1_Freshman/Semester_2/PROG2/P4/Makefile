all:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e1 p4_e1.c tree.c integer.c
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e2 p4_e2.c tree.c integer.c
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e3 p4_test-node-tree.c tree.c node.c
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_e4 p4_e4.c tree.c functions.c

run_e1:
	valgrind --leak-check=full --track-origins=yes ./exe_e1 data.txt

run_e2:
	valgrind --leak-check=full --track-origins=yes ./exe_e2 data.txt

run_e3:
	valgrind --leak-check=full --track-origins=yes ./exe_e3 dict10.dat

run_e4:
	valgrind --leak-check=full --track-origins=yes ./exe_e4 strings.txt
