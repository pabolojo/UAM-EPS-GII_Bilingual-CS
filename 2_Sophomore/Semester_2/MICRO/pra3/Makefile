# MBS 2020. LAB 3
#
# Team Number XX:

all: pract3.exe clear

pract3.exe: pract3.obj pract3a.obj
	tcc -v -ml -Lc:\compila\tc\lib pract3.obj pract3a.obj

pract3.obj: pract3.c
	tcc -c -v -ml -Ic:\compila\tc\include pract3.c
 
pract3a.obj: pract3a.asm
	tasm /zi /ml pract3a,,pract3a 

clear:
	del *.obj
	del *.map
	del *.lst

clean: clear
	del *.exe

