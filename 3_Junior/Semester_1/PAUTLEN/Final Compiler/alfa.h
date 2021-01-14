#ifndef _ALFA_H
#define _ALFA_H

#include "symbolTable.h"
#include "generacion.h"

#define MAX_LONG_ID 100
#define MAX_TAMANIO_VECTOR 64

/* CLASES */
#define ESCALAR 0
#define VECTOR 1

/* TYPES */
#define INT 0
#define BOOLEAN 1

/* CATEGORY OF ELEMENTS */
#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3

typedef struct _tipo_atributos
{
    char lexema[MAX_LONG_ID + 1];
    int tipo;
    int valor_entero;
    int es_direccion;
    int etiqueta;
} tipo_atributos;

#endif