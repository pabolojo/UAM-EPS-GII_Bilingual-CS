/* 
    Made by:
    Group:
        1391
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

#define MAX_LENGTH 100

FILE* yyin;
FILE* yyout;
int num_column = 1;
int morfo_error = 0;

%}
 /**yylineno stores the number of line in which we are**/
%option yylineno
%option noyywrap

/**To avoid unused variables warnings, we just add these two lines**/
%option nounput
%option noinput

DIGIT [0-9]
IDENTIFIER [a-z][a-z0-9]*
TAB "\t"
NEWLINE "\n"
SPACE " "
COMMENT (" //"|"//")+([ |0-9|a-z|A-Z|@|_|%|:|<|>|?|¿|!|¡|=]*)+"\n"
ERROR [^{DIGIT}|{IDENTIFIER}|{VOID}|{COMMENT}]

%%  

"main" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAIN;
}

"int" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_INT;
}

"boolean" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_BOOLEAN;
}

"array" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ARRAY;
}

"function" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_FUNCTION;
}

"if" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_IF;
}

"else" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ELSE;
}

"while" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_WHILE;
}

"scanf" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_SCANF;
}

"printf" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PRINTF;
}

"return" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_RETURN;
}

";" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PUNTOYCOMA;
}

"," {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_COMA;
}

"(" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PARENTESISIZQUIERDO;
}

")" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_PARENTESISDERECHO;
}

"[" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CORCHETEIZQUIERDO;
}

"]" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CORCHETEDERECHO;
}

"{" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_LLAVEIZQUIERDA;
}

"}" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_LLAVEDERECHA;
}

"=" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ASIGNACION;
}

"+" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAS;
}

"-" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENOS;
}

"/" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_DIVISION;
}

"*" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_ASTERISCO;
}

"&&" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_AND;
}

"||" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_OR;
}

"!" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_NOT;
}

"==" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_IGUAL;
}

"!=" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_DISTINTO;
}

"<=" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENORIGUAL;
}

">=" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAYORIGUAL;
}

"<" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MENOR;
}

">" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_MAYOR;
}

("-"|"+")?{DIGIT}+ {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_CONSTANTE_ENTERA;
}

"true" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_TRUE;
}

"false" {
    num_column += yyleng;
    fprintf(yyout, ";D:\t%s\n", yytext);
    return TOK_FALSE;
}

{COMMENT} {
    num_column = 1;
    /** Reset the line number and ignores a void action **/
}

{TAB} {
    num_column += 4;
    /**  Add 4 spaces and ignores a void action**/
}

{SPACE} {
    num_column++;
    /** Have into account the scape size in the column and ignores a void action **/
}

{NEWLINE} {
    num_column = 1;
    /** Reset the line number and ignores a void action **/
}

{IDENTIFIER} {
    num_column += yyleng;
    if(yyleng <= MAX_LENGTH){
        fprintf(yyout, ";D:\t%s\n", yytext);
        return TOK_IDENTIFICADOR;

    }else{
        fprintf(stderr,"****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", yylineno, num_column-yyleng, yytext);
        return TOK_ERROR;
    }
}

{ERROR} {
    num_column += yyleng;
    fprintf(stderr,"****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", yylineno, num_column-yyleng, yytext);
    morfo_error = 1;
    return TOK_ERROR;
}

%%


