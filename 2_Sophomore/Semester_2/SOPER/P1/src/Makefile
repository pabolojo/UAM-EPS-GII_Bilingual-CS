
CC = gcc
CFLAGS = -pedantic
EXE = ejercicio_arbol ejercicio_shell ejercicio_shell_spawn

all : $(EXE) ejercicio_pipes ejercicio_hilos

.PHONY : clean
clean :
	rm -f *.o core $(EXE) ejercicio_pipes ejercicio_hilos

$(EXE) : % : %.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -o $@ $@.o

ejercicio_hilos : % : %.o funciones_hilos.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -pthread -o $@ $@.o funciones_hilos.o

ejercicio_pipes : % : %.o funciones_pipes.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -o $@ $@.o funciones_pipes.o

 ejercicio_arbol.o : ejercicio_arbol.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 ejercicio_hilos.o : ejercicio_hilos.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

 ejercicio_pipes.o : ejercicio_pipes.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 ejercicio_shell.o : ejercicio_shell.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 ejercicio_shell_spawn.o : ejercicio_shell_spawn.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 funciones_pipes.o :  funciones_pipes.c funciones_pipes.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 funciones_hilos.o :  funciones_hilos.c funciones_hilos.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<
