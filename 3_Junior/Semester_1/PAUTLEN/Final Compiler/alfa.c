/* 
    Made by:
    Group:
        1391
*/
#include <stdio.h>
#include "alfa.h"
#include "y.tab.h"

extern FILE *yyin;
extern FILE *yyout;
extern int num_column;
extern int yylineno;
extern int yyleng;

int main(int argc, char *argv[])
{
    int last_token;

    if (argc != 3)
    {
        printf("ERROR you must use ./pruebaSintactico <input.txt> <output.txt>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        printf("ERROR opening <input.txt>\n");
        return 1;
    }

    yyout = fopen(argv[2], "w");
    if (!yyout)
    {
        printf("ERROR creating <output.txt>\n");
        return 1;
    }

    if (initializeSymbolTable() == -1)
    {
        printf("ERROR creating SymbolTable\n");
        return 1;
    }

    /* Write the bss header before starting the yyparser */
	escribir_cabecera_bss(yyout); 

    yyparse();

    deleteSymbolTable();

    fclose(yyin);
    yyin = NULL;

    fclose(yyout);
    yyout = NULL;

    return 0;
}


