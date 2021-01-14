/* 
    Made by:
    Group:
        1391
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

Element *elementIni(char *identifier, ElemCategory elem_category, Type type, Category category, int value, int position, int num_vars)
{
    Element *new = NULL;

    if (!identifier)
    {
        printf("ERROR in the parameters of elementIni\n");
        return NULL;
    }

    new = (Element *)malloc(sizeof(Element));
    if (!new)
    {
        printf("ERROR while allocating memory in elementIni\n");
        return NULL;
    }

    new->identifier = strdup(identifier);
    if (!new->identifier)
    {
        printf("ERROR while allocating memory in elementIni\n");
        return NULL;
    }

    new->elem_category = elem_category;
    new->type = type;
    new->category = category;
    new->value = value;
    new->position = position;
    new->num_vars = num_vars;

    return new;
}

void freeElement(Element *e)
{
    if (e)
    {
        if (e->identifier)
        {
            free(e->identifier);
            e->identifier = NULL;
        }

        free(e);
    }
}

ElementRow *elementRowIni()
{
    ElementRow *new = NULL;

    new = (ElementRow *)malloc(sizeof(ElementRow));
    if (!new)
    {
        printf("ERROR while allocating memory in elementRowIni\n");
        return NULL;
    }

    new->row = NULL;

    new->num_elems = 0;

    return new;
}

void elementRowFree(ElementRow *e)
{
    int i;

    if (e)
    {
        for (i = 0; i < e->num_elems; ++i)
        {
            freeElement(e->row[i]);
            e->row[i] = NULL;
        }

        free(e->row);
        free(e);
    }
    return;
}

HashTable *hashTableIni(int capacity)
{
    HashTable *new = NULL;
    int i;

    new = (HashTable *)malloc(sizeof(HashTable));
    if (!new)
    {
        printf("ERROR while allocating memory in hashTableIni\n");
        return NULL;
    }

    new->capacity = capacity;

    /* Static alloc for the table */
    new->table = (ElementRow **)malloc(sizeof(ElementRow *) * capacity);

    if (!new->table)
    {
        printf("ERROR while allocating memory in hashTableIni\n");
        return NULL;
    }

    /* Creates all rows at the beginning */
    for (i = 0; i < new->capacity; ++i)
    {
        new->table[i] = elementRowIni();
    }

    return new;
}

void hashTableFree(HashTable *e)
{
    int i;

    if (e)
    {
        for (i = 0; i < e->capacity; ++i)
        {
            elementRowFree(e->table[i]);
            e->table[i] = NULL;
        }

        free(e->table);
        free(e);
    }
    return;
}

int elementInsert(ElementRow *row, Element *e)
{
    if (!row || !e)
        return -1;

    if ((row->row) == NULL)
    { /* First insertion */
        row->row = (Element **)malloc(sizeof(Element *));
        if(!row->row){
            printf("Error reserving memory in elementInsert\n");
            return -1;
        }
    }
    else
    { /* If there is a colision */
        row->row = (Element **)realloc(row->row, sizeof(Element *) * (row->num_elems + 1));
        if(!row->row){
            printf("Error reallocating memory in elementInsert\n");
            return -1;
        }
    }

    row->row[row->num_elems] = e;
    ++(row->num_elems);

    return 0;
}

int elementSearch(ElementRow *row, char *identifier)
{
    int i;

    if (!row || !identifier)
        return -1;

    for (i = 0; i < row->num_elems; ++i)
    {
        if (strcmp(identifier, (row->row[i]->identifier)) == 0)
        { /* if equal */
            return i;
        }
    }

    return -1;
}

long elementHash(unsigned char *str)
{
    unsigned long hash = CAPACITY;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % CAPACITY;
}

int tableInsert(HashTable *table, Element *e)
{
    int index = 0;
    ElementRow *indexRow = NULL;

    if (!table || !e)
        return -1;

    index = elementHash(e->identifier);
    indexRow = table->table[index];

    if (elementSearch(indexRow, e->identifier) != -1)
    { /*If duplicated entry*/
        freeElement(e);
        return -1;
    }
    else
    {
        elementInsert(indexRow, e);
        return 0;
    }
}

Element *tableSearch(HashTable *table, char *e)
{
    int index, row_index;
    ElementRow *indexRow = NULL;

    if (!table || !e)
        return NULL;

    index = elementHash(e);
    indexRow = table->table[index];
    row_index = elementSearch(indexRow, e);

    if (row_index == -1)
    { /* If there is no such elem in the table */
        return NULL;
    }

    return indexRow->row[row_index];
}


