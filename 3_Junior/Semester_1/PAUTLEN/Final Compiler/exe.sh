./alfa ./test_cases/while.alf prueba.asm
nasm -g -felf32 prueba.asm
gcc -m32 -o prueba -g alfalib.o prueba.o
