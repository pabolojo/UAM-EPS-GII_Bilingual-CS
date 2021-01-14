/* 
    Made by:
    Group:
        1391
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfa.h"

void yyerror(char *msg);
extern FILE* yyout;
extern int yylineno;
extern int yyleng;
extern int num_column;
extern int morfo_error;
extern int yylex();

/* global variables from the spanish slices   */
/* we keep their name, just in case it is use */
/* by the professor                           */
int tipo_actual;                                                                
int clase_actual;

/* Functions variables, slide 36*/
int num_variables_locales_actual;
int pos_variable_local_actual;
int num_parametros_actual;
int pos_parametro_actual;
int tipo_funcion_actual;
int is_function = 0;
int return_declared = 0;

int tamanio_vector_actual;

/*char indice_vector_actual[MAX_LONG_ID + 1];*/

/* Control function arguments*/
int nested_call = 0;    /* funct(a, funct(..)) is disallowed */
int aux_params;         /* parameter count */

/* Tag count */
int etiqueta = 1;
%}

%union
{
  tipo_atributos atrib;
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

%token <atrib> TOK_IDENTIFICADOR
%token <atrib> TOK_CONSTANTE_ENTERA

/* Declaring the semantic value of the non-terminal items*/
%type <atrib> conditional
%type <atrib> if_exp
%type <atrib> if_exp_sentences
%type <atrib> if_else_exp_sentences
%type <atrib> loop_ini
%type <atrib> loop_exp
%type <atrib> comparison
%type <atrib> vector_element
%type <atrib> exp
%type <atrib> constant
%type <atrib> integer_constant
%type <atrib> logic_constant
%type <atrib> identifier
%type <atrib> fn_name
%type <atrib> fn_declaration
%type <atrib> goto_func

%token <atrib> TOK_TRUE
%token <atrib> TOK_FALSE

%token TOK_ERROR

/* First declared has less precedence */
%left TOK_IGUAL TOK_DISTINTO TOK_MENOR TOK_MAYOR TOK_MENORIGUAL TOK_MAYORIGUAL
%left TOK_OR
%left TOK_AND
%left TOK_MENOS TOK_MAS
%left TOK_DIVISION TOK_ASTERISCO

%right TOK_NOT
%start axiom 

%%

/** We have identify the rules by the column line in the ALFA grammar page given by the professor **/
/** For example axiom is the rule number 1 --> R1 **/

axiom: TOK_MAIN TOK_LLAVEIZQUIERDA declarations write1 functions write2 sentences TOK_LLAVEDERECHA {
    escribir_fin(yyout);
    fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");
    };


write1:{
    escribir_subseccion_data(yyout);
    escribir_segmento_codigo(yyout);
};

write2:{
    escribir_inicio_main(yyout);
};

declarations: declaration { fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n"); }
            | declaration declarations { fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n"); };

declaration:  class identifiers TOK_PUNTOYCOMA { fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n"); };

class:  class_scalar { 
        clase_actual = ESCALAR;
        fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");
    }
    |  class_vector {
        clase_actual = VECTOR;
        fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");    
    };

class_scalar:   type { fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n"); };

type:   TOK_INT {
        tipo_actual = INT;
        fprintf(yyout, ";R10:\t<tipo> ::= int\n");
    }
    |   TOK_BOOLEAN {
        tipo_actual = BOOLEAN;
        fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");
    };

class_vector:  TOK_ARRAY type TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {
        
        if(($4.valor_entero < 1) || ($4.valor_entero > MAX_TAMANIO_VECTOR)){
            fprintf(stderr, "****Error semantico en lin %d: El tamanyo del vector <nombre_vector> excede los limites permitidos (1,64).\n", yylineno);
            return TOK_ERROR;
        }
        
        if(is_function){
            fprintf(stderr, "****Error semantico en lin %d: Declaracion de vector en funcion no permitida.\n", yylineno);
            return TOK_ERROR;   
        }
        
        tamanio_vector_actual = $4.valor_entero;
        fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ constante_entera ]\n");
    };

identifiers:  identifier { fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n"); }
           |  identifier TOK_COMA identifiers { fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n"); };

functions:  function functions { fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n"); }
         |  /* lambda */ { fprintf(yyout, ";R21:\t<funciones> ::= \n"); };

function:  fn_declaration sentences TOK_LLAVEDERECHA {
    Element* ret = NULL;

    if(!return_declared) {
        fprintf(stderr,"****Error semantico en lin %d: Funcion %s sin sentencia de retorno.\n", yylineno, $1.lexema);
		return TOK_ERROR;
    }
    
    deleteScope();
    return_declared = 0;
    is_function = 0;

    ret = searchSymbol($1.lexema);
    if(ret == NULL){
        fprintf(stderr,"****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylineno, $1.lexema);
        return TOK_ERROR;
    }
    
    ret->num_params = num_parametros_actual;
    
    fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
};

fn_name: TOK_FUNCTION type TOK_IDENTIFICADOR {

    if(createScope($3.lexema, -2, tipo_actual)){ /* Any function must have a negative value */
        fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada.", yylineno);
    }

    $$.tipo = tipo_actual;
    tipo_funcion_actual = tipo_actual;
    strcpy($$.lexema, $3.lexema);

    num_variables_locales_actual = 0; /* we get the names from the theory slides */
    pos_variable_local_actual = 1;
    num_parametros_actual = 0;
    pos_parametro_actual = 0;
    is_function = 1;
};

fn_declaration: fn_name TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations {
    Element* ret = searchSymbol($1.lexema);
    if (ret == NULL)
    {
        fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylineno, $1.lexema);
        return TOK_ERROR;
    }

    ret->num_params = num_parametros_actual;
    $$.tipo = tipo_actual;
    strcpy($$.lexema, $1.lexema);

    declararFuncion(yyout, $1.lexema, num_variables_locales_actual);
};

function_params:  function_param rest_params_function { fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n"); }
               |  /* lambda */ { fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n"); };
               
rest_params_function:  TOK_PUNTOYCOMA function_param rest_params_function { fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n"); }
                    |  /* lambda */ { fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n"); };
 
function_param: type fn_identifier {
        num_parametros_actual++;
        pos_parametro_actual++;
        fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");
};

fn_identifier: TOK_IDENTIFICADOR {
        Element *ret = searchSymbol_local($1.lexema);
        if(ret != NULL) {
            fprintf(stderr,"****Error semantico en lin %d: Declaracion duplicada.\n", yylineno);
			return TOK_ERROR;
        }

        insertSymbol($1.lexema, tipo_actual, clase_actual, PARAMETRO, $1.valor_entero);
        ret = searchSymbol_local($1.lexema);
        ret->num_params = num_parametros_actual;
};

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
               
block:  conditional { fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n"); }
     |  loop { fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n"); };

assignment:  TOK_IDENTIFICADOR TOK_ASIGNACION exp {
                Element* ret = searchSymbol($1.lexema);
                
                if (ret == NULL)
                {
                    fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylineno, $1.lexema);
                    return TOK_ERROR;
                }
                if (ret->elem_category == FUNCION) /* Es funcion ? */
                {
                    fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
                    return TOK_ERROR;
                }
                if (ret->type != $3.tipo)
                {
                    fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
                    return TOK_ERROR;
                }

                if(is_function) {
                    if(ret->elem_category == PARAMETRO) {
                        escribirParametro(yyout, ret->num_params, num_parametros_actual);
                    }
                    else {
                        escribirVariableLocal(yyout, ret->num_vars + 1);
                    }
                    asignarDestinoEnPila(yyout, $3.es_direccion);
                }
                else {
                    asignar(yyout, $1.lexema, $3.es_direccion);
                    fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
                }
            }
          | vector_element TOK_ASIGNACION exp {
            Element* ret = searchSymbol($1.lexema);
            if($1.tipo != $3.tipo){
                fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
                return TOK_ERROR;
            }

            asignarVectorEnPila(yyout, $3.es_direccion);      /*Asignamos valor a vector + offset*/
            fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
    };
          
vector_element: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
        Element* ret = searchSymbol($1.lexema);

        if(ret->elem_category == FUNCION) {
            fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
            return TOK_ERROR;
        }
        
        if (ret->category != VECTOR)
        {
            fprintf(stderr, "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n", yylineno);
            return TOK_ERROR;
        }

        if($3.tipo != INT) { /* we only allow index vectors of integer type */
            fprintf(stderr, "****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero.\n", yylineno);
            return TOK_ERROR;
        }
        
        $$.es_direccion = 1;
        strcpy($$.lexema, $1.lexema);
        $$.tipo = ret->type;

        escribir_elemento_vector(yyout, $1.lexema, ret->value, $3.es_direccion);
        fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
    };

conditional:  if_exp_sentences TOK_LLAVEDERECHA {
                    ifthen_fin(yyout, $1.etiqueta);
                    fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n"); }
            |  if_else_exp_sentences sentences TOK_LLAVEDERECHA {
                    ifthenelse_fin(yyout, $1.etiqueta);
                    fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n"); 
                };

if_exp_sentences:	if_exp sentences {
            $$.etiqueta = $1.etiqueta;
        };

if_else_exp_sentences: if_exp_sentences TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA {
            ifthenelse_fin_then(yyout, $1.etiqueta);
            $$.etiqueta = $1.etiqueta;
        };
        
if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
            if($3.tipo != BOOLEAN){
                fprintf(stderr, "****Error semantico en lin %d: Condicional con condicion de tipo int.\n", yylineno);
                return TOK_ERROR;
            }
            
            $$.etiqueta = etiqueta++; /* It first assign the tag and then increment its value */
            ifthenelse_inicio(yyout, $3.es_direccion, $$.etiqueta);
        };

loop: loop_exp sentences TOK_LLAVEDERECHA {
        while_fin(yyout, $1.etiqueta);
        fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
    };

loop_ini: TOK_WHILE TOK_PARENTESISIZQUIERDO{      
        $$.etiqueta = etiqueta++; /* It first assign the tag and then increment its value */
        while_inicio(yyout, $$.etiqueta);
    };

loop_exp: loop_ini exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
        if($2.tipo != BOOLEAN){
            fprintf(stderr, "****Error semantico en lin %d: Bucle con condicion de tipo int.\n", yylineno);
            return TOK_ERROR;
        }
        while_exp_pila(yyout, $1.es_direccion, $$.etiqueta);
    };

read:  TOK_SCANF TOK_IDENTIFICADOR {
        Element* ret = searchSymbol($2.lexema);
        if(ret == NULL){ /* If we search and it is not in the table */
            fprintf(stderr,"****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylineno, $2.lexema);
            return TOK_ERROR;
        }

        if(ret->category != ESCALAR) { /* It is not an escalar */
            fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
            return TOK_ERROR;
        }
        else if(ret->elem_category != VARIABLE) { /* It is not a variable */
            fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", yylineno);
            return TOK_ERROR;
        }

        leer(yyout, $2.lexema, $2.tipo);
        fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador>\n");
    };

write:  TOK_PRINTF exp {
        escribir(yyout, $2.es_direccion, $2.tipo);
        fprintf(yyout, ";R56:\t<escritura> ::= printf <exp>\n");
    };

function_return:  TOK_RETURN exp {
        if(!is_function){
            fprintf(stderr, "****Error semantico en lin %d: Sentencia de retorno fuera del cuerpo de una función.\n", yylineno);
            return TOK_ERROR;
        }
        
        if(tipo_funcion_actual != $2.tipo) {
            fprintf(stderr, "****Error semantico en lin %d: Sentencia de retorno con distinto tipo que la función.\n", yylineno);
            return TOK_ERROR;
        }

        return_declared = 1;
        retornarFuncion(yyout, $2.es_direccion);
        fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp>\n");
    };

exp:  exp TOK_MAS exp { 
            if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", yylineno);
                return TOK_ERROR;
            }
            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if (($1.tipo == INT) && ($3.tipo == INT))
            {
                sumar(yyout, $1.es_direccion, $3.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = INT;
                $$.es_direccion = 0;
            }

            fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n"); 
        }
    |  exp TOK_MENOS exp { 
                if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                {
                    fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", yylineno);
                    return TOK_ERROR;
                }
                /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
                if (($1.tipo == INT) && ($3.tipo == INT))
                {
                    restar(yyout, $1.es_direccion, $3.es_direccion);

                    /* We propagate correctly the attributes */
                    $$.tipo = INT;
                    $$.es_direccion = 0;
                }
                
                fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
            }
    |  exp TOK_DIVISION exp {
            if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", yylineno);
                return TOK_ERROR;
            }
            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if (($1.tipo == INT) && ($3.tipo == INT))
            {
                dividir(yyout, $1.es_direccion, $3.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = INT;
                $$.es_direccion = 0;
            }
            fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
        }
    |  exp TOK_ASTERISCO exp {
            if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", yylineno);
                return TOK_ERROR;
            }

            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if (($1.tipo == INT) && ($3.tipo == INT))
            {
                multiplicar(yyout, $1.es_direccion, $3.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = INT;
                $$.es_direccion = 0;
            }

            fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n"); 
        }
    |  TOK_MENOS exp {
            if ($2.tipo == BOOLEAN)
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", yylineno);
                return TOK_ERROR;
            }

            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if ($2.tipo == INT)
            {
                cambiar_signo(yyout, $2.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = INT;
                $$.es_direccion = 0;
            }

            fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
        }
    |  exp TOK_AND exp {
            if (($1.tipo == INT) || ($3.tipo == INT))
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", yylineno);
                return TOK_ERROR;
            }

            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if (($1.tipo == BOOLEAN) && ($3.tipo == BOOLEAN))
            {
                y(yyout, $1.es_direccion, $3.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            
            fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
        }
    |  exp TOK_OR exp {
            if (($1.tipo == INT) || ($3.tipo == INT))
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", yylineno);
                return TOK_ERROR;
            }
            
            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if (($1.tipo == BOOLEAN) && ($3.tipo == BOOLEAN))
            {
                o(yyout, $1.es_direccion, $3.es_direccion);

                /* We propagate correctly the attributes */
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }

            fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
        }
    |  TOK_NOT exp { 
            if ($2.tipo == INT)
            {
                fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", yylineno);
                return TOK_ERROR;
            }
            
            /* Sólo se puede generar código si se intenta sumar dos subexpresiones enteras*/
            if ($2.tipo == BOOLEAN)
            {
                no(yyout, $2.es_direccion, etiqueta);
                etiqueta++;

                /* We propagate correctly the attributes */
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }

            fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n"); 
        }
    |  TOK_IDENTIFICADOR {
            Element* ret = searchSymbol($1.lexema);
            if (ret == NULL)
            {
                fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", yylineno, $1.lexema);
                return TOK_ERROR;
            }

            if(is_function) {
                if(ret->elem_category == PARAMETRO) {
                    escribirParametro(yyout, ret->num_params, num_parametros_actual);
                }
                else {
                    escribirVariableLocal(yyout, ret->num_vars + 1); /* ebp +1*4 DO NOT REMOVE*/
                }
            }
            else {
                escribir_operando(yyout, $1.lexema, 1); /*  It is always a variable*/
            }

            strcpy($$.lexema, $1.lexema);
            $$.tipo = ret->type;
            $$.es_direccion = 1;    /* It is a variable */

            fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n");
        }
    |  constant { 
            $$.tipo = $1.tipo;
            $$.es_direccion = $1.es_direccion;
            fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");
        }
    |  TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {
            $$.tipo = $2.tipo;
            $$.es_direccion = $2.es_direccion;                
            fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");
        }
    |  TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO {
            $$.tipo = $2.tipo;
            $$.es_direccion = $2.es_direccion;

            fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");
        }
    |  vector_element {
            fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n");
        }
    |  goto_func expresion_list TOK_PARENTESISDERECHO {
            Element *ret = searchSymbol($1.lexema);

            if(!ret) {
                fprintf(stderr, "****Error semantico en lin %d: Funcion no declarada (%s).\n", yylineno, $1.lexema);
                return TOK_ERROR;
            }
            if(ret->elem_category != FUNCION){
                fprintf(stderr, "****Error semantico en lin %d: El identificador no es una funcion (%s).\n", yylineno, $1.lexema);
                return TOK_ERROR;
            }

            if(ret->num_params != aux_params) {
                fprintf(stderr, "****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion.\n", yylineno);
                return TOK_ERROR;
            }
            
            nested_call = 0;
            $$.tipo = ret->type;
            llamarFuncion(yyout, $1.lexema, ret->num_params);

            fprintf(yyout, ";R88:\t<exp> ::= ( <lista_expresiones> )\n");
        };

goto_func: TOK_IDENTIFICADOR TOK_PARENTESISIZQUIERDO {
    if(nested_call){
        fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n", yylineno);
        return TOK_ERROR;
    }

    nested_call = 1;
    aux_params = 0;
    strcpy($$.lexema, $1.lexema);
};

expresion_list:  push_exp remaining_expresion_list {
        nested_call = 0;
        aux_params++;
        fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");
    }
              | /*Lambda*/ { nested_call = 0; fprintf(yyout, ";R90:\t<lista_expresiones> ::= \n"); };

remaining_expresion_list:  TOK_COMA push_exp remaining_expresion_list { 
        aux_params++;
        fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");
    }
    | /*Lambda*/ { fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::= \n");
    };

push_exp: exp {
        operandoEnPilaAArgumento(yyout, $1.es_direccion);
    };

comparison:  exp TOK_IGUAL exp {
                    if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                    {
                        fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                        return TOK_ERROR;
                    }

                    if (($1.tipo == INT) && ($3.tipo == INT))
                    {
                        igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                        etiqueta++;
                        /* We propagate correctly the attributes */
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                    }

                    fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
                }
            |  exp TOK_DISTINTO exp {
                    if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                    {
                        fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                        return TOK_ERROR;
                    }

                    if (($1.tipo == INT) && ($3.tipo == INT))
                    {
                        distinto(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                        etiqueta++;
                        /* We propagate correctly the attributes */
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                    }
                    fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
                }
            |  exp TOK_MENORIGUAL exp {
                    if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                    {
                        fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                        return TOK_ERROR;
                    }

                    if (($1.tipo == INT) && ($3.tipo == INT))
                    {
                        menor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                        etiqueta++;
                        /* We propagate correctly the attributes */
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                    }
                    
                    fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");
                }
            |  exp TOK_MAYORIGUAL exp {
                    if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                    {
                        fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                        return TOK_ERROR;
                    }

                    if (($1.tipo == INT) && ($3.tipo == INT))
                    {
                        mayor_igual(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                        etiqueta++;
                        /* We propagate correctly the attributes */
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                    }

                    fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp>\n"); 
                }
            |  exp TOK_MENOR exp { 
                    if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                    {
                        fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                        return TOK_ERROR;
                    }

                    if (($1.tipo == INT) && ($3.tipo == INT))
                    {
                        menor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                        etiqueta++;
                        /* We propagate correctly the attributes */
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                    }
                fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp>\n");
                }
            |  exp TOK_MAYOR exp {
                if (($1.tipo == BOOLEAN) || ($3.tipo == BOOLEAN))
                {
                    fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", yylineno);
                    return TOK_ERROR;
                }

                if (($1.tipo == INT) && ($3.tipo == INT))
                {
                    mayor(yyout, $1.es_direccion, $3.es_direccion, etiqueta);
                    etiqueta++;
                    /* We propagate correctly the attributes */
                    $$.tipo = BOOLEAN;
                    $$.es_direccion = 0;
                }  

                fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
            };
           
constant:  logic_constant { fprintf(yyout, ";R99:\t<constante> ::= <constante_logica>\n"); }
        |  integer_constant {
            $$.tipo = $1.tipo;
            $$.es_direccion = $1.es_direccion;
            fprintf(yyout, ";R100:\t<constante> ::= <constante_entera>\n");
        };
         
logic_constant:  TOK_TRUE {
                    $$.tipo = BOOLEAN;
                    $$.es_direccion = 0;

                    char buffer[20];
                    sprintf(buffer, "%d", 1);
                    escribir_operando(yyout, (char *)(buffer), $$.es_direccion);
                    fprintf(yyout, ";R102:\t<constante_logica> ::= true\n");
                }
                |  TOK_FALSE {
                    $$.tipo = BOOLEAN;
                    $$.es_direccion = 0;
                      
                    char buffer[20];
                    sprintf(buffer, "%d", 0);
                    escribir_operando(yyout, (char *)(buffer), $$.es_direccion);
                    fprintf(yyout, ";R103:\t<constante_logica> ::= false\n");
                };

integer_constant:  TOK_CONSTANTE_ENTERA {
        $$.tipo = INT;
        $$.es_direccion = 0;
        $$.valor_entero = $1.valor_entero;

        char buffer[20];
        sprintf(buffer, "%d", $1.valor_entero);

         escribir_operando(yyout, (char *)(buffer), $$.es_direccion);

        fprintf(yyout, ";R104:\t<constante_entera> ::= <numero>\n"); 
    };

identifier:  TOK_IDENTIFICADOR {
    Element* ret = searchSymbol($1.lexema);

    if((ret != NULL) && (ret->elem_category != FUNCION)){ /* Si lo buscas y ya existe */
        fprintf(stderr,"****Error semantico en lin %d: Declaracion duplicada.\n", yylineno);
        return TOK_ERROR;
    }else{
        insertSymbol($1.lexema, tipo_actual, clase_actual, VARIABLE, $1.valor_entero);

        if(is_function) {
            ret = searchSymbol($1.lexema);
            
            if(clase_actual == VECTOR) {
				fprintf(stderr, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", yylineno);
				return TOK_ERROR;
			}
            
			ret->num_vars = num_variables_locales_actual;
            ret->num_params = num_parametros_actual;

			num_variables_locales_actual++;
			pos_variable_local_actual++;
        }
        else {
            int tamanio = 1;
            if(clase_actual == VECTOR) {
                tamanio = tamanio_vector_actual;
            }
            declarar_variable(yyout, $1.lexema, tipo_actual, tamanio);
        }

        fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n"); };
    }
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


