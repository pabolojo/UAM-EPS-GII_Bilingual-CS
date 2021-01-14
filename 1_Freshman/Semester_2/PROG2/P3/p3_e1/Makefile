queue:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe node.c p3_e1.c queue.c graph.c
queue_test:
	gcc -g -ansi -pedantic -std=c99 -Wall -o exe_test node.c p3_testqueue.c queue.c
run_queue_test:
	valgrind --leak-check=full --track-origins=yes ./exe_test nodes.txt
run_queue:
	valgrind --leak-check=full --track-origins=yes ./exe archivo 1 5
