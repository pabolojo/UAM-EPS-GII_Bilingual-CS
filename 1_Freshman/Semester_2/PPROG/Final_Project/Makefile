#-----------------------
# Makefile
#-----------------------

CC = gcc -pedantic -ansi
CFLAGS = -Wall -g

SRC=./src
INCLUDE = ./include
OBJ = ./obj
DOC = ./doc
TEST = ./test
BIN = ./bin
BINTEST = ./test/bin
OBJTEST = ./test/obj
EXE = $(BIN)/game_loop 
TEST1 = $(BINTEST)/space_test
TEST2 = $(BINTEST)/die_test
TEST3 = $(BINTEST)/link_test
TEST4 = $(BINTEST)/object_test
TEST5 = $(BINTEST)/inventory_test
TEST6 = $(BINTEST)/player_test
TEST7 = $(BINTEST)/set_test
TEST8 = $(BINTEST)/dialogue_test

OBJETOS =  $(OBJ)/game_loop.o $(OBJ)/space.o $(OBJ)/object.o $(OBJ)/player.o $(OBJ)/die.o $(OBJ)/set.o $(OBJ)/link.o $(OBJ)/inventory.o $(OBJ)/dialogue.o $(OBJ)/game.o $(OBJ)/command.o $(OBJ)/screen.o $(OBJ)/graphic_engine.o $(OBJ)/game_management.o $(OBJ)/game_rules.o  

all : $(EXE) $(TEST1) $(TEST2) $(TEST3) $(TEST4) $(TEST5) $(TEST6) $(TEST7) $(TEST8)

.PHONY : all

$(EXE) :$(OBJETOS)
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJETOS)

$(TEST1): $(OBJTEST)/space_test.o $(OBJ)/space.o $(OBJ)/link.o $(OBJ)/set.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/space_test.o $(OBJ)/space.o $(OBJ)/link.o $(OBJ)/set.o

$(OBJTEST)/space_test.o : $(TEST)/space_test.c $(TEST)/space_test.h $(TEST)/test.h $(INCLUDE)/space.h $(INCLUDE)/link.h $(INCLUDE)/set.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST2): $(OBJTEST)/die_test.o $(OBJ)/die.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/die_test.o $(OBJ)/die.o

$(OBJTEST)/die_test.o : $(TEST)/die_test.c $(TEST)/die_test.h $(TEST)/test.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST3): $(OBJTEST)/link_test.o $(OBJ)/link.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/link_test.o $(OBJ)/link.o

$(OBJTEST)/link_test.o : $(TEST)/link_test.c $(TEST)/link_test.h $(TEST)/test.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST4): $(OBJTEST)/object_test.o $(OBJ)/object.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/object_test.o $(OBJ)/object.o

$(OBJTEST)/object_test.o : $(TEST)/object_test.c $(TEST)/object_test.h $(TEST)/test.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST5): $(OBJTEST)/inventory_test.o $(OBJ)/inventory.o $(OBJ)/set.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/inventory_test.o $(OBJ)/inventory.o $(OBJ)/set.o

$(OBJTEST)/inventory_test.o : $(TEST)/inventory_test.c $(TEST)/inventory_test.h $(TEST)/test.h $(INCLUDE)/set.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST6): $(OBJTEST)/player_test.o $(OBJ)/player.o $(OBJ)/set.o $(OBJ)/inventory.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/player_test.o $(OBJ)/player.o $(OBJ)/set.o $(OBJ)/inventory.o

$(OBJTEST)/player_test.o : $(TEST)/player_test.c $(TEST)/player_test.h $(TEST)/test.h $(INCLUDE)/set.h $(INCLUDE)/types.h $(TEST)/inventory_test.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST7): $(OBJTEST)/set_test.o $(OBJ)/set.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/set_test.o $(OBJ)/set.o

$(OBJTEST)/set_test.o : $(TEST)/set_test.c $(TEST)/set_test.h $(TEST)/test.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST8): $(OBJTEST)/dialogue_test.o $(OBJ)/dialogue.o $(OBJ)/command.o 
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS)  -o $@ $(OBJTEST)/dialogue_test.o $(OBJ)/dialogue.o $(OBJ)/command.o 

$(OBJTEST)/dialogue_test.o : $(TEST)/dialogue_test.c $(TEST)/dialogue_test.h $(TEST)/test.h $(INCLUDE)/command.h $(INCLUDE)/types.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/game_loop.o : $(SRC)/game_loop.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/space.o : $(SRC)/space.c $(INCLUDE)/space.h $(INCLUDE)/set.h $(INCLUDE)/types.h $(INCLUDE)/link.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/player.o : $(SRC)/player.c $(INCLUDE)/player.h $(INCLUDE)/set.h $(INCLUDE)/types.h $(INCLUDE)/inventory.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/object.o : $(SRC)/object.c $(INCLUDE)/object.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/set.o : $(SRC)/set.c $(INCLUDE)/set.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/die.o : $(SRC)/die.c $(INCLUDE)/die.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/command.o : $(SRC)/command.c $(INCLUDE)/command.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/link.o : $(SRC)/link.c $(INCLUDE)/link.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/inventory.o : $(SRC)/inventory.c $(INCLUDE)/inventory.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/dialogue.o : $(SRC)/dialogue.c $(INCLUDE)/dialogue.h $(INCLUDE)/types.h $(INCLUDE)/command.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/game.o : $(SRC)/game.c $(INCLUDE)/game.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/game_management.o : $(SRC)/game_management.c $(INCLUDE)/game_management.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/screen.o : $(SRC)/screen.c $(INCLUDE)/screen.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/graphic_engine.o : $(SRC)/graphic_engine.c $(INCLUDE)/graphic_engine.h $(INCLUDE)/screen.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/game_rules.o : $(SRC)/game_rules.c $(INCLUDE)/game_rules.h $(INCLUDE)/game.h $(INCLUDE)/types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< -o $@
	
.PONY: clean
clean :
	rm $(OBJ)/*.o && rm -rf doc && rm $(OBJTEST)/*.o

clear :
	rm $(OBJ)/*.o && rm -rf doc && rm Doxyfile && rm $(OBJTEST)/*.o

dist: 
	tar zcvf ../p4.tgz *

doxygen: Doxyfile 
	doxygen Doxyfile 
	
Doxyfile:
	mkdir doc
	doxygen -g
	sed -i 's/HTML_OUTPUT            = html/HTML_OUTPUT            = doc\/html/g' Doxyfile &&  sed -i 's/INPUT                  =/INPUT                  = src include/g' Doxyfile &&  sed -i 's/LATEX_OUTPUT           = latex/LATEX_OUTPUT           = doc\/latex/g' Doxyfile
	
 	 
