all: factor.exe factor2.exe

factor.exe: factor.obj
	tlink /v factor

factor.obj: factor.asm
	tasm /zi factor.asm


factor2.exe: factor2.obj
	tlink /v factor2

factor2.obj: factor2.asm
	tasm /zi factor2.asm