/* 
    Made by:
    Group:
        1391
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define MAX_LENGTH 100

FILE* yyin;
FILE* yyout;

%}
 /**yylineno stores the number of line in which we are**/
%option yylineno
%option noyywrap

/**To avoid unused variables warnings, we just add these two lines**/
%option nounput
%option noinput

DIGIT "-"?[0-9]+
SCOPE [a-z][a-z0-9]*
IDENTIFIER [a-z][a-z]*

%%  

"cierre -999" {
    deleteScope();
    fprintf(yyout, "cierre");

    return 1;
}

{IDENTIFIER}" "{DIGIT} {
    char* identifier = strtok(yytext, " ");

    int value = atoi(strtok(NULL, " "));

    if(insertSymbol(identifier, value) == -1){
        fprintf(yyout, "-1 %s", identifier); /*Failure insertion*/
    }else{
        fprintf(yyout, "%s", identifier);
    }

    return 1;
}

{SCOPE}" "{DIGIT} {
    char* identifier = strtok(yytext, " ");

    int value = atoi(strtok(NULL, " "));

    if(createScope(identifier, value) == -1){
        fprintf(yyout, "-1 %s", identifier);
        return 1;
    }

    fprintf(yyout, "%s", identifier);
    
    return 1;
}

{IDENTIFIER} {
    int res = searchSymbol(yytext);
    fprintf(yyout, "%s %d", yytext, res);
    return 1;
}

{SCOPE} {
    int res = searchSymbol(yytext);
    fprintf(yyout, "%s %d", yytext, res);
    
    return 1;
}

%%

int main(int argc, char *argv[]) {
    int last_token;
    
    if(argc != 3) {
        printf("ERROR you must use ./prueba_tabla <input.txt> <output.txt>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if(!yyin){
        printf("ERROR opening <input.txt>\n");
        return 1;
    }

    yyout = fopen(argv[2], "w");
    if(!yyout){
        printf("ERROR creating <output.txt>\n");
        return 1;
    }

    if(initializeSymbolTable()) {
        fclose(yyin);
        yyin = NULL;

        fclose(yyout);
        yyout = NULL;
    }



    while( (last_token = yylex())  != 0) {
        if(last_token == -1) break;
    }

    deleteSymbolTable();

    fclose(yyin);
    yyin = NULL;

    fclose(yyout);
    yyout = NULL;

    return 0;
}



