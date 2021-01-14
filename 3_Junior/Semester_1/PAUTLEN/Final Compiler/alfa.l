/* TODO ELIMINAR printfs y cambiar strcopy general
    Made by:
    Group:
        1391
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfa.h"
#include "y.tab.h"

#define MAX_LENGTH 100
#define YY_USER_ACTION { num_column += yyleng; }

int num_column = 1;
int morfo_error = 0;

%}

/**yylineno stores the number of line in which we are**/
%option yylineno
%option noyywrap

/**To avoid unused variables warnings, we just add these two lines**/
%option nounput
%option noinput

DIGIT [0-9]*
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
TAB "\t"
NEWLINE "\n"
SPACE " "
COMMENT "//".*
ERROR .

%%  

"main" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAIN;
}

"int" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_INT;
}

"boolean" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_BOOLEAN;
}

"array" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ARRAY;
}

"function" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_FUNCTION;
}

"if" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_IF;
}

"else" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ELSE;
}

"while" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_WHILE;
}

"scanf" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_SCANF;
}

"printf" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PRINTF;
}

"return" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_RETURN;
}

";" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PUNTOYCOMA;
}

"," {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_COMA;
}

"(" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PARENTESISIZQUIERDO;
}

")" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PARENTESISDERECHO;
}

"[" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CORCHETEIZQUIERDO;
}

"]" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CORCHETEDERECHO;
}

"{" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_LLAVEIZQUIERDA;
}

"}" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_LLAVEDERECHA;
}

"=" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ASIGNACION;
}

"+" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAS;
}

"-" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENOS;
}

"/" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_DIVISION;
}

"*" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ASTERISCO;
}

"&&" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_AND;
}

"||" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_OR;
}

"!" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_NOT;
}

"==" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_IGUAL;
}

"!=" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_DISTINTO;
}

"<=" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENORIGUAL;
}

">=" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAYORIGUAL;
}

"<" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENOR;
}

">" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAYOR;
}

{DIGIT} {
    yylval.atrib.valor_entero = atoi(yytext);
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CONSTANTE_ENTERA;
}

"true" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_TRUE;
}

"false" {
    strcpy(yylval.atrib.lexema, yytext);
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_FALSE;
}

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

{IDENTIFIER} {
    strcpy(yylval.atrib.lexema, yytext);

    if(yyleng <= MAX_LENGTH){
        fprintf(yyout, ";D:\t%s\n", yytext);
        return TOK_IDENTIFICADOR;

    }else{
        fprintf(stderr,"****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", yylineno, num_column-yyleng, yytext);
        return TOK_ERROR;
    }
}

{ERROR} {
    fprintf(stderr,"****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", yylineno, num_column-yyleng, yytext);
    morfo_error = 1;
    return TOK_ERROR;
}

%%


