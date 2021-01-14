CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc

EXE = odbc-connection-test dvdreq dvdfilm dvdrent

all : clean $(EXE)

$(EXE) : % : %.o odbc.o functions.o

clean :
	rm -f *.o core $(EXE)



