figures: main.o f1.o f2.o f3.o f4.o f5.o f6.o f7.o
	gcc -o figures main.o f1.o f2.o f3.o f4.o f5.o f6.o f7.o

f1.o: f1.c fig.h
	gcc -c f1.c

f2.o: f2.c fig.h
	gcc -c f2.c

f3.o: f3.c fig.h
	gcc -c f3.c

f4.o: f4.c fig.h
	gcc -c f4.c

f5.o: f5.c fig.h
	gcc -c f5.c

f6.o: f6.c fig.h
	gcc -c f6.c

f7.o: f7.c fig.h
	gcc -c f7.c

main.o: main.c fig.h
	gcc -c main.c

clean:
	rm *.o
