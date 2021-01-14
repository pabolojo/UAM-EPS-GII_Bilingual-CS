/* 
    Made by:
    Group:
        1391
*/

#include <stdio.h>
#include "hashTable.h"

HashTable *globalTable = NULL;
HashTable *localTable = NULL;

int initializeSymbolTable()
{
    if (globalTable)
    {
        return 0;
    }

    globalTable = hashTableIni(CAPACITY);

    if (!globalTable)
    {
        return -1;
    }
    return 0;
}

void deleteSymbolTable()
{
    if (localTable)
    {
        hashTableFree(localTable);
        localTable = NULL;
    }
    if (globalTable)
    {
        hashTableFree(globalTable);
        globalTable = NULL;
    }
}

int insertSymbol(char *identifier, int value)
{
    Element *e = NULL;
    int res;

    if (!globalTable | !identifier | value <= -1)
    {
        printf("ERROR in the parameters insertSymbol\n");
        return -1;
    }
    
    e = elementIni(identifier, 1, 1, 1, value, 1, 1);

    if (!e)
    {
        printf("ERROR while creating an element\n");
        return -1;
    }

    if (localTable)
    {
        return tableInsert(localTable, e);
    }

    return tableInsert(globalTable, e);
}

int searchSymbol(char *identifier)
{
    if (!identifier)
    {
        return -1;
    }

    Element *result;

    /* If the local table exists, we are in a local area*/
    if (localTable)
    {
        result = tableSearch(localTable, identifier);
        if (result)
        {
            return result->value;
        }
    }

    /* If the local table does not exist, we look in the global table */
    result = tableSearch(globalTable, identifier);
    if (result)
    {
        return result->value;
    }

    return -1;
}

int createScope(char *identifier, int value)
{
    Element *scp = NULL, *scp_copy = NULL;

    if (!identifier || localTable != NULL || value > -1)
    { /* If there is another local scope */
        return -1;
    }
    else
    {
        localTable = hashTableIni(CAPACITY);
        if(!localTable){
            printf("ERROR in the call to hashTableIni inside createScope\n");
            return -1;
        }
        
        scp = elementIni(identifier, 1, 1, 1, value, 1, 1);
        if(!scp){
            printf("ERROR in the first call to elementIni inside createScope\n");
            return -1;
        }
        /* Fast way to make a copy */
        scp_copy = elementIni(identifier, 1, 1, 1, value, 1, 1);
        if(!scp_copy){
            printf("ERROR in the second call to elementIni inside createScope\n");
            return -1;
        }

        /* We insert the table in its own */
        if (tableInsert(localTable, scp) == -1)
        {
            printf("ERROR in the first call to tableInsert inside createScope\n");
            return -1;
        }

        /* We insert the local table into the global one */
        if (tableInsert(globalTable, scp_copy) == -1)
        {
            printf("ERROR in the second call to tableInsert inside createScope\n");
            return -1;
        }
    }

    return 0;
}

void deleteScope()
{
    if (localTable)
    {
        hashTableFree(localTable);
        localTable = NULL;
    }
}


