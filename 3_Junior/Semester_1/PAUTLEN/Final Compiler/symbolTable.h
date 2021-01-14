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
int insertSymbol(char *identifier, Type t, Category c, ElemCategory class, int value);
Element* searchSymbol(char *identifier);
Element * searchSymbol_local(char *identifier);
int createScope(char *identifier, int value, Type type);
void deleteScope();

#endif


