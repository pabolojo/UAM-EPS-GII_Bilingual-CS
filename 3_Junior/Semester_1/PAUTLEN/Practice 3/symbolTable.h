/* 
    Made by:
    Group:
        1391
*/
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "hashTable.h"

int initializeSymbolTable();
void deleteSymbolTable();
int insertSymbol(char *identifier, int value);
int searchSymbol(char *identifier);
int createScope(char *identifier, int value);
void deleteScope();

#endif


