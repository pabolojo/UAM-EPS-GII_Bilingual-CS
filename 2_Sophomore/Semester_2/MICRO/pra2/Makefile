# MBS 2020. LAB 2
#
# Team Number XX:

all: pract2a.exe pract2b.exe pract2c.exe

pract2a.exe: pract2a.obj wav.obj
	tlink /v pract2a wav

pract2a.obj: pract2a.asm
	tasm /zi pract2a.asm

pract2b.exe: pract2b.obj wav.obj
	tlink /v pract2b wav

pract2b.obj: pract2b.asm
	tasm /zi pract2b.asm


pract2c.exe: pract2c.obj wav.obj
	tlink /v pract2c wav

pract2c.obj: pract2c.asm
	tasm /zi pract2c.asm


clear:
	del p*.obj
	del p*.map

clean:
	del p*.obj
	del p*.map
	del *.exe
	del *.wav


