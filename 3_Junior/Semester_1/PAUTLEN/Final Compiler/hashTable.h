/* Category of the  element */
typedef enum
{
    VARIABLE = 1,
    PARAMETRO,
    FUNCION
} ElemCategory;

/* Data Type */
typedef enum
{
    INT = 0,
    BOOLEAN 
} Type;

/* Category */
typedef enum
{
    ESCALAR = 0,
    VECTOR
} Category;

/* Vector Constraints */
#define MIN_VECT 1
#define MAX_VECT 64
#define CAPACITY 5381

typedef struct _Element
{
    char *identifier; /* Name of the variable (lexema) */
    ElemCategory elem_category;
    Type type;
    Category category;
    int value; /* If type == VARIABLE -->  It can be a value, a length in case of a vector*/
    int num_vars;
    int pos_vars;
    int num_params;
    int pos_params;
} Element;

typedef struct _ElementRow
{
    Element **row;
    int num_elems;

} ElementRow;

typedef struct _HashTable
{
    ElementRow **table;
    int capacity;

} HashTable;

HashTable *hashTableIni(int capacity);
void hashTableFree(HashTable *e);

Element *elementIni(char *identifier, ElemCategory elem_category, Type type, Category category, int value, int num_vars, int pos_vars, int num_params, int pos_params);
int tableInsert(HashTable *table, Element *e);
Element *tableSearch(HashTable *table, char *e);