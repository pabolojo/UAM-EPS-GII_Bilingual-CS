CC=gcc

CFLAGS=-g -Wall -pedantic -ansi -Iinclude

all:compress goose_game doxy 
	@echo ATTENTION! THE SCREEN MUST BE MADE GREATER!

goose_game: command.o game.o game_loop.o graphic_engine.o screen.o space.o gamemanagement.o player.o object.o set.o die.o link.o inventory.o game_rules.o dialogue.o
	$(CC) -o goose_game  command.o game.o game_loop.o graphic_engine.o screen.o space.o gamemanagement.o player.o object.o set.o die.o link.o inventory.o game_rules.o dialogue.o
	mv *.o obj/

command.o: src/command.c
	$(CC) $(CFLAGS) -c src/command.c

game_rules.o: src/game_rules.c
	$(CC) $(CFLAGS) -c src/game_rules.c

game.o: src/game.c
	$(CC) $(CFLAGS) -c src/game.c

game_loop.o: src/game_loop.c
	$(CC) $(CFLAGS) -c src/game_loop.c

graphic_engine.o: src/graphic_engine.c
	$(CC) $(CFLAGS) -c src/graphic_engine.c

screen.o: src/screen.c
	$(CC) $(CFLAGS) -c src/screen.c

space.o: src/space.c
	$(CC) $(CFLAGS) -c src/space.c

gamemanagement.o: src/gamemanagement.c
	$(CC) $(CFLAGS) -c src/gamemanagement.c

player.o: src/player.c
	$(CC) $(CFLAGS) -c src/player.c

object.o: src/object.c
	$(CC) $(CFLAGS) -c src/object.c

set.o: src/set.c
	$(CC) $(CFLAGS) -c src/set.c

die.o: src/die.c
	$(CC) $(CFLAGS) -c src/die.c

link.o: src/link.c
	$(CC) $(CFLAGS) -c src/link.c

inventory.o: src/inventory.c
	$(CC) $(CFLAGS) -c src/inventory.c

dialogue.o: src/dialogue.c
	$(CC) $(CFLAGS) -c src/dialogue.c

compress:
	tar -cvzf I4.tgz src include Makefile

val:
	valgrind --leak-check=full --track-origins=yes ./goose_game data.dat -l logfile

clean:
	rm -rf obj/*.o

doxy:
	mv src/* ./
	mv include/* ./
	mv doc/Doxyfile ./
	doxygen Doxyfile
	mv *.c src/
	mv *.h include/
	rm -r doc/
	mkdir doc
	mv Doxyfile ./doc
	mv latex/ doc/
	mv html/ doc/
