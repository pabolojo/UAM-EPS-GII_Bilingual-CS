/* 
    Made by:
    Group:
        1391
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char *msg);
extern FILE* yyout;
extern int yylineno;
extern int yyleng;
extern int num_column;
extern int morfo_error;
extern int yylex();
%}

%union
{
  char* string;
  int digit;
}

/* Reserved words */ 
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

/* Symbols */
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS TOK_MENOS
%token TOK_ASTERISCO TOK_DIVISION
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

%token <string> TOK_IDENTIFICADOR
%token <digit> TOK_CONSTANTE_ENTERA

%token TOK_TRUE
%token TOK_FALSE

%token TOK_ERROR

%left TOK_IGUAL TOK_DISTINTO TOK_MENOR TOK_MAYOR TOK_MENORIGUAL TOK_MAYORIGUAL
%left TOK_AND TOK_OR
%left TOK_MENOS TOK_MAS
%left TOK_DIVISION TOK_ASTERISCO

%right TOK_NOT
%start axiom 

%%

/** We have identify the rules by the column line in the ALFA grammar page given by the professor **/
/** For example axiom is the rule number 1 --> R1 **/

axiom:  TOK_MAIN TOK_LLAVEIZQUIERDA declarations functions sentences TOK_LLAVEDERECHA { fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n"); };

declarations: declaration { fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n"); }
            | declaration declarations { fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n"); };

declaration:  class identifiers TOK_PUNTOYCOMA { fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n"); };

class:  class_scalar { fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n"); }
     |  class_vector { fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n"); };

class_scalar:   type { fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n"); };

type:   TOK_INT { fprintf(yyout, ";R10:\t<tipo> ::= int\n"); }
    |   TOK_BOOLEAN { fprintf(yyout, ";R11:\t<tipo> ::= boolean\n"); };

class_vector:   TOK_ARRAY type TOK_CORCHETEIZQUIERDO integer_constant TOK_CORCHETEDERECHO { fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ constante_entera ]\n"); };

identifiers:  identifier { fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n"); }
           |  identifier TOK_COMA identifiers { fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n"); };

functions:  function functions { fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n"); }
         |  /* lambda */ { fprintf(yyout, ";R21:\t<funciones> ::= \n"); };

function:  TOK_FUNCTION type identifier TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations sentences TOK_LLAVEDERECHA { fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n"); };

function_params:  function_param rest_params_function { fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n"); }
               |  /* lambda */ { fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n"); };
               
rest_params_function:  TOK_PUNTOYCOMA function_param rest_params_function { fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n"); }
                    |  /* lambda */ { fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n"); };

function_param: type identifier { fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n"); };

function_declarations:  declarations { fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n"); }
                     |  /* lambda */ { fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n"); };

sentences:  sentence { fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n"); }
         |  sentence sentences { fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n"); };

sentence:  simple_sentence TOK_PUNTOYCOMA { fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n"); }
        |  block { fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n"); };

simple_sentence:  assignment { fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n"); }
               |  read { fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n"); }
               |  write { fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n"); }
               |  function_return { fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n"); };
               
block:  conditional { fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\nn"); }
     |  loop { fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n\n"); };

assignment:  identifier TOK_ASIGNACION exp { fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n"); }
          |  vector_element TOK_ASIGNACION exp { fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n"); };
          
vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO { fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n"); };

conditional:  TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentences TOK_LLAVEDERECHA { fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n"); } 
           |  TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentences TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentences TOK_LLAVEDERECHA { fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n"); };

loop:  TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentences TOK_LLAVEDERECHA { fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n"); };

read:  TOK_SCANF identifier { fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador>\n"); };

write:  TOK_PRINTF exp { fprintf(yyout, ";R56:\t<escritura> ::= printf <exp>\n"); };

function_return:  TOK_RETURN exp { fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp>\n"); };

exp:  exp TOK_MAS exp { fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n"); }
   |  exp TOK_MENOS exp { fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n"); }
   |  exp TOK_DIVISION exp { fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n"); }
   |  exp TOK_ASTERISCO exp { fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n"); }
   |  TOK_MENOS exp { fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n"); }
   |  exp TOK_AND exp { fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n"); }
   |  exp TOK_OR exp { fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n"); }
   |  TOK_NOT exp { fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n"); }
   |  identifier  { fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n"); }
   |  constant  { fprintf(yyout, ";R81:\t<exp> ::= <constante>\n"); }
   |  TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO { fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n"); }
   |  TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO { fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n"); }
   |  vector_element { fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n"); }
   |  identifier TOK_PARENTESISIZQUIERDO expresion_list TOK_PARENTESISDERECHO { fprintf(yyout, ";R88:\t<exp> ::= ( <lista_expresiones> )\n"); };

expresion_list:  exp remaining_expresion_list { fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n"); }
              | /*Lambda*/ { fprintf(yyout, ";R90:\t<lista_expresiones> ::= \n"); };

remaining_expresion_list:  TOK_COMA exp remaining_expresion_list {fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n"); }
                        | /*Lambda*/ { fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::= \n"); };

comparison:  exp TOK_IGUAL exp { fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp>\n"); }
          |  exp TOK_DISTINTO exp {fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp>\n"); }
          |  exp TOK_MENORIGUAL exp { fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp>\n"); }
          |  exp TOK_MAYORIGUAL exp { fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp>\n"); }
          |  exp TOK_MENOR exp { fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp>\n"); }
          |  exp TOK_MAYOR exp { fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp>\n"); };
           
constant:  logic_constant { fprintf(yyout, ";R99:\t<constante> ::= <constante_logica>\n"); }
        |  integer_constant { fprintf(yyout, ";R100:\t<constante> ::= <constante_entera>\n"); };
         
logic_constant:  TOK_TRUE { fprintf(yyout, ";R102:\t<constante_logica> ::= true\n"); }
              |  TOK_FALSE { fprintf(yyout, ";R103:\t<constante_logica> ::= false\n"); };

integer_constant:  TOK_CONSTANTE_ENTERA { fprintf(yyout, ";R104:\t<constante_entera> ::= <numero>\n"); };

identifier:  TOK_IDENTIFICADOR { fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n"); };

%%

void yyerror(char *s)
{
    if (morfo_error)
    {
        morfo_error = 0;
    }
    else
    {
        fprintf(stderr, "****Error sintactico en [lin %d, col %d]\n", yylineno, num_column - yyleng);
    }
}


