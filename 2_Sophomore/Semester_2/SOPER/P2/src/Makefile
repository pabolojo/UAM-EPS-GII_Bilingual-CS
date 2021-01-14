
CC = gcc
CFLAGS = -pedantic -Wall
EXE = ejercicio_kill ejercicio_prottemp ejercicio_lect_escr
EXE2 = ejercicio_prottemp_mejorado ejercicio_prottemp_mejorado_op

all : $(EXE) $(EXE2)

.PHONY : clean
clean :
	rm -f *.o core $(EXE) $(EXE2)

$(EXE) : % : %.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -pthread -o $@ $@.o

$(EXE2) : % : %.o funciones_prottemp_mejorado.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -pthread -o $@ $@.o funciones_prottemp_mejorado.o

 ejercicio_kill.o : ejercicio_kill.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 ejercicio_prottemp.o : ejercicio_prottemp.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

 ejercicio_lect_escr.o : ejercicio_lect_escr.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

 ejercicio_prottemp_mejorado.o : ejercicio_prottemp_mejorado.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

 ejercicio_prottemp_mejorado_op.o : ejercicio_prottemp_mejorado_op.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

 funciones_prottemp_mejorado.o :  funciones_prottemp_mejorado.c funciones_prottemp_mejorado.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<
