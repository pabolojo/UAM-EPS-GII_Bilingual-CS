#-----------------------
# IMPORTANT: The value of the parameters of exercise?_test should be adjusted.
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = exercise4 exercise5

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# $< has changed"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed$<"
	$(CC) $(CFLAGS) -c $<

 sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed$<"
	$(CC) $(CFLAGS) -c $<

 times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed$<"
	gcc -pedantic $(CFLAGS) -c $<

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 10

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 1 -num_max 5 -incr 1 -numP 5 -outputFile exercise5.log
