/* Category of the  element */
typedef enum{
    VARIABLE = 1,
    PARAMETRO,
    FUNCION
} ElemCategory;

/* Data Type */
typedef enum{
    BOOLEAN = 1,
    INT
} Type;

/* Category */
typedef enum{
    ESCALAR = 1,
    VECTOR
} Category;

/* Vector Constraints */
#define MIN_VECT 1
#define MAX_VECT 64
#define CAPACITY 5381

typedef struct _Element{
    char* identifier;        /* Name of the variable */
    ElemCategory elem_category;
    Type type;
    Category category;
    int value;    /* If type == VARIABLE -->  It can be a value, a length in case of a vector or the number of parameters in case of a function*/
    int position;
    int num_vars;
    
} Element;

typedef struct _ElementRow{  
    Element** row;
    int num_elems; 

} ElementRow;

typedef struct _HashTable{  
    ElementRow** table;
    int capacity; 

} HashTable;


HashTable * hashTableIni(int capacity);
void hashTableFree(HashTable* e);

Element * elementIni(char* identifier, ElemCategory elem_category, Type type, Category category, int value, int position, int num_vars);

int tableInsert(HashTable * table, Element *e);
Element* tableSearch(HashTable * table, char *e);