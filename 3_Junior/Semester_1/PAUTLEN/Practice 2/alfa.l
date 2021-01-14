*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

int num_column = 1;

#define MAX_LENGTH 100
#define YY_USER_ACTION { num_column += yyleng; }

FILE* yyin;
FILE* yyout;


%}
 /**yylineno stores the number of line in which we are**/
%option yylineno
%option noyywrap

/**To avoid unused variables warnings, we just add these two lines**/
%option nounput
%option noinput

DIGIT [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
TAB "\t"
NEWLINE "\n"
SPACE " "
COMMENT "//".*
ERROR .

%%  

"main" {return TOK_MAIN;}

"int" {return TOK_INT;}

"boolean" {return TOK_BOOLEAN;}

"array" {return TOK_ARRAY;}

"function" {return TOK_FUNCTION;}

"if" {return TOK_IF;}

"else" {return TOK_ELSE;}

"while" {return TOK_WHILE;}

"scanf" {return TOK_SCANF;}

"printf" {return TOK_PRINTF;}

"return" {return TOK_RETURN;}

";" {return TOK_PUNTOYCOMA;}

"," {return TOK_COMA;}

"(" {return TOK_PARENTESISIZQUIERDO;}

")" {return TOK_PARENTESISDERECHO;}

"[" {return TOK_CORCHETEIZQUIERDO;}

"]" {return TOK_CORCHETEDERECHO;}

"{" {return TOK_LLAVEIZQUIERDA;}

"}" {return TOK_LLAVEDERECHA;}

"=" {return TOK_ASIGNACION;}

"+" {return TOK_MAS;}

"-" {return TOK_MENOS;}

"/" {return TOK_DIVISION;}

"*" {return TOK_ASTERISCO;}

"&&" {return TOK_AND;}

"||" {return TOK_OR;}

"!" {return TOK_NOT;}

"==" {return TOK_IGUAL;}

"!=" {return TOK_DISTINTO;}

"<=" {return TOK_MENORIGUAL;}

">=" {return TOK_MAYORIGUAL;}

"<" {return TOK_MENOR;}

">" {return TOK_MAYOR;}

{DIGIT} {return TOK_CONSTANTE_ENTERA;}

"true" {return TOK_TRUE;}

"false" {return TOK_FALSE;}

{COMMENT} {
    num_column = 1;
    /** Reset the line number and ignores a void action **/
}

{TAB} {
    yyleng += 4;
    /**  Add 4 spaces and ignores a void action**/
}

{SPACE} {
    yyleng++;
    /** Have into account the scape size in the column and ignores a void action **/
}

{NEWLINE} {
    num_column = 1;
    /** Reset the line number and ignores a void action **/
}

{IDENTIFIER} { return TOK_IDENTIFICADOR; }

{ERROR} { return TOK_ERROR; }

%%

int main(int argc, char *argv[]) {
    int last_token;
    
    if(argc != 3) {
        printf("ERROR you must use ./pruebaMorfo <input.txt> <output.txt>\n");
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

    while( (last_token = yylex())  != 0) {
        switch(last_token){
            case TOK_MAIN:
                fprintf(yyout, "TOK_MAIN\t%d main\n", TOK_MAIN);
                break;
            case TOK_INT:
                fprintf(yyout, "TOK_INT\t%d int\n", TOK_INT);
                break;
            case TOK_BOOLEAN:
                fprintf(yyout, "TOK_BOOLEAN\t%d boolean\n", TOK_BOOLEAN);
                break;
            case TOK_ARRAY:
                fprintf(yyout, "TOK_ARRAY\t%d array\n", TOK_ARRAY);
                break;
            case TOK_FUNCTION:
                fprintf(yyout, "TOK_FUNCTION\t%d function\n", TOK_FUNCTION);
                break;
            case TOK_IF:
                fprintf(yyout, "TOK_IF\t%d if\n", TOK_IF);
                break;
            case TOK_ELSE:
                fprintf(yyout, "TOK_ELSE\t%d else\n", TOK_ELSE);
                break;
            case TOK_WHILE:
                fprintf(yyout, "TOK_WHILE\t%d while\n", TOK_WHILE);
                break;
            case TOK_SCANF:
                fprintf(yyout, "TOK_SCANF\t%d scanf\n", TOK_SCANF);
                break;
            case TOK_PRINTF:
                fprintf(yyout, "TOK_PRINTF\t%d printf\n", TOK_PRINTF);
                break;
            case TOK_RETURN:
                fprintf(yyout, "TOK_RETURN\t%d return\n", TOK_RETURN);
                break;
            case TOK_PUNTOYCOMA:
                fprintf(yyout, "TOK_PUNTOYCOMA\t%d ;\n",TOK_PUNTOYCOMA);
                break;               
            case TOK_COMA:
                fprintf(yyout, "TOK_COMA\t%d ,\n",TOK_COMA);
                break;
            case TOK_PARENTESISIZQUIERDO:
                fprintf(yyout, "TOK_PARENTESISIZQUIERDO\t%d (\n",TOK_PARENTESISIZQUIERDO);
                break;
            case TOK_PARENTESISDERECHO:
                fprintf(yyout, "TOK_PARENTESISDERECHO\t%d )\n",TOK_PARENTESISDERECHO);
                break;
            case TOK_CORCHETEIZQUIERDO:
                fprintf(yyout, "TOK_CORCHETEIZQUIERDO\t%d [\n",TOK_CORCHETEIZQUIERDO);
                break;
            case TOK_CORCHETEDERECHO:
                fprintf(yyout, "TOK_CORCHETEDERECHO\t%d ]\n",TOK_CORCHETEDERECHO);
                break;
            case TOK_LLAVEIZQUIERDA:
                fprintf(yyout, "TOK_LLAVEIZQUIERDA\t%d {\n",TOK_LLAVEIZQUIERDA);
                break;
            case TOK_LLAVEDERECHA:
                fprintf(yyout, "TOK_LLAVEDERECHA\t%d }\n",TOK_LLAVEDERECHA);
                break;
            case TOK_ASIGNACION:
                fprintf(yyout, "TOK_ASIGNACION\t%d =\n",TOK_ASIGNACION);
                break;
            case TOK_MAS:
                fprintf(yyout, "TOK_MAS\t%d +\n",TOK_MAS);
                break;
            case TOK_MENOS:
                fprintf(yyout, "TOK_MENOS\t%d -\n",TOK_MENOS);
                break;
            case TOK_DIVISION:
                fprintf(yyout, "TOK_DIVISION\t%d /\n",TOK_DIVISION);
                break;
            case TOK_ASTERISCO:
                fprintf(yyout, "TOK_ASTERISCO\t%d *\n",TOK_ASTERISCO);
                break;
            case TOK_AND:
                fprintf(yyout, "TOK_AND\t%d &&\n",TOK_AND);
                break;
            case TOK_OR:
                fprintf(yyout, "TOK_OR\t%d ||\n",TOK_OR);
                break;
            case TOK_NOT:
                fprintf(yyout, "TOK_NOT\t%d !\n", TOK_NOT);
                break;
            case TOK_IGUAL:
                fprintf(yyout, "TOK_IGUAL\t%d ==\n", TOK_IGUAL);
                break;
            case TOK_DISTINTO:
                fprintf(yyout, "TOK_DISTINTO\t%d !=\n", TOK_DISTINTO);
                break;
            case TOK_MENORIGUAL:
                fprintf(yyout, "TOK_MENORIGUAL\t%d <=\n", TOK_MENORIGUAL);
                break;
            case TOK_MAYORIGUAL:
                fprintf(yyout, "TOK_MAYORIGUAL\t%d >=\n", TOK_MAYORIGUAL);
                break;
            case TOK_MENOR:
                fprintf(yyout, "TOK_MENOR\t%d <\n", TOK_MENOR);
                break;
            case TOK_MAYOR:
                fprintf(yyout, "TOK_MAYOR\t%d >\n", TOK_MAYOR);
                break;
            case TOK_CONSTANTE_ENTERA:
                fprintf(yyout, "TOK_CONSTANTE_ENTERA\t%d %s\n", TOK_CONSTANTE_ENTERA, yytext);
                break;
            case TOK_TRUE:
                fprintf(yyout, "TOK_TRUE\t%d true\n", TOK_TRUE);
                break;
            case TOK_FALSE:
                fprintf(yyout, "TOK_FALSE\t%d false\n", TOK_FALSE);
                break;
            case TOK_IDENTIFICADOR:
                if(yyleng <= MAX_LENGTH){
                    fprintf(yyout, "TOK_IDENTIFICADOR\t%d %s\n", TOK_IDENTIFICADOR, yytext);
                }else{
                    fprintf(stderr,"****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", yylineno, num_column-yyleng, yytext);
                    
                    fclose(yyin);
                    yyin = NULL;

                    fclose(yyout);
                    yyout = NULL;

                    return -1;
                }

                break;
            case TOK_ERROR:
                fprintf(stderr,"****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", yylineno, num_column-yyleng, yytext);

                fclose(yyin);
                yyin = NULL;

                fclose(yyout);
                yyout = NULL;

                return -1;
        }     
    }

    fclose(yyin);
    yyin = NULL;

    fclose(yyout);
    yyout = NULL;

    return 0;
}



