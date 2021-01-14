CC=gcc

CFLAGS=-g -Wall -pedantic -ansi

all:goose_game compress

goose_game: command.o game.o game_loop.o graphic_engine.o screen.o space.o gamereader.o player.o object.o set.o die.o
	$(CC) -o goose_game  command.o game.o game_loop.o graphic_engine.o screen.o space.o gamereader.o player.o object.o set.o die.o

command.o: command.c
	$(CC) $(CFLAGS) -c command.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

game_loop.o: game_loop.c
	$(CC) $(CFLAGS) -c game_loop.c

graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c
	$(CC) $(CFLAGS) -c space.c

gameReader.o: gamereader.c
	$(CC) $(CFLAGS) -c gamereader.c

player.o: player.c
	$(CC) $(CFLAGS) -c player.c

object.o: object.c
	$(CC) $(CFLAGS) -c object.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

die.o: die.c
		$(CC) $(CFLAGS) -c die.c

compress:
	tar -cvzf I2.tgz *.c *.h Makefile

val:
	valgrind --leak-check=full --track-origins=yes ./goose_game data.dat -l logfile

clean:
	rm -rf *.o
