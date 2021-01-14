#include "tree.h"

typedef struct _NodeBT {
void* info;
struct _NodeBT* left;
struct _NodeBT* right;
} NodeBT;

struct _Tree {
 NodeBT *root;
 destroy_elementtree_function_type destroy_element_function;
 copy_elementtree_function_type copy_element_function;
 print_elementtree_function_type print_element_function;
 cmp_elementtree_function_type cmp_element_function;
};

void tree_freeRec(NodeBT* pn, destroy_elementtree_function_type f);
void destroyNodeAB(NodeBT *pn, destroy_elementtree_function_type f);
Status tree_insertRec(NodeBT** ppn, const void*po, copy_elementtree_function_type f, cmp_elementtree_function_type c);
NodeBT * iniNodeAB();
int tree_preOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p);
int printNodeAB(FILE* pf, const NodeBT *pn, print_elementtree_function_type f);
int tree_inOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p);
int tree_postOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p);
int tree_depthRec(NodeBT* pn);
int tree_numNodesRec(NodeBT* pn);
NodeBT *lookAB(const Tree *pa, const void* po);
NodeBT *lookABRec(NodeBT* pn, const void* po, cmp_elementtree_function_type c);
int tree_printRec(FILE* f, NodeBT* pn, int depth, print_elementtree_function_type p);

/* Initialize an empty tree. */
Tree* tree_ini(
 destroy_elementtree_function_type f1,
 copy_elementtree_function_type f2,
 print_elementtree_function_type f3,
 cmp_elementtree_function_type f4){
   Tree *t=NULL;
   t=(Tree*)malloc(sizeof(Tree));
   if(!t) return NULL;
   t->root=NULL;
   t->destroy_element_function=f1;
   t->copy_element_function=f2;
   t->print_element_function=f3;
   t->cmp_element_function=f4;
   return t;
 }
/* Indicates if the tree is empty or not. */
Bool tree_isEmpty( const Tree *pa){
  if(!pa) return TRUE;
  if(!pa->root || !pa->root->info) return TRUE;
  return FALSE;
}
/* Frees the memory used by a Tree.*/
void tree_free(Tree *pa){
  if(!pa) return;
  tree_freeRec(pa->root,pa->destroy_element_function);
  free(pa);
  pa=NULL;
}

void tree_freeRec(NodeBT* pn, destroy_elementtree_function_type f){
    if(!pn) return;
    tree_freeRec(pn->left,f);
    tree_freeRec(pn->right,f);
    destroyNodeAB(pn,f);
}

/*Frees the memory used by a node of the Tree.*/
void destroyNodeAB(NodeBT *pn, destroy_elementtree_function_type f){
  if(!pn) return;
  f(pn->info);
  free(pn);
  pn=NULL;
}
/* Inserts an element into a binary search tree by copying it into new memory. */
Status tree_insert(Tree *pa, const void *po){
  if(!pa || !po) return ERROR;
  return tree_insertRec(&pa->root,po,pa->copy_element_function,pa->cmp_element_function);
}

Status tree_insertRec(NodeBT** ppn, const void*po, copy_elementtree_function_type f, cmp_elementtree_function_type c){
  int cmp;
  if(!ppn || !po) return ERROR;
  if(!(*ppn)){
    *ppn=iniNodeAB();
    if(!(*ppn)) return ERROR;
    (*ppn)->info=f(po);
    if (!((*ppn)->info)) {
      free((*ppn));
      return ERROR;
    }
    return OK;
  }
  cmp=c(po,(*ppn)->info);
  if(cmp==0){
    return ERROR;
  }
  else if(cmp>0){
    return tree_insertRec(&((*ppn)->right),po,f,c);
  }
  else{
    return tree_insertRec(&((*ppn)->left),po,f,c);
  }
  return ERROR;
}

/*Create a node of the Tree*/
NodeBT * iniNodeAB(){
   NodeBT *aux=NULL;
   aux=(NodeBT*)malloc(sizeof(NodeBT));
   if(!aux) return NULL;
   aux->info=NULL;
   aux->left=NULL;
   aux->right=NULL;
   return aux;
}
/*Writes in the file f the path of a tree in previous order without modifying it. */
int tree_preOrder(FILE *f, const Tree *pa){
  if(!f || !pa) return ERROR;
  return tree_preOrderRec(f,pa->root,pa->print_element_function);
}

int tree_preOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p){
  int chars=0;
   if(!f || !pn) return ERROR;
   chars+=printNodeAB(f, pn, p);
   tree_preOrderRec(f,pn->left,p);
   tree_preOrderRec(f,pn->right,p);
   return chars;
}

/*Print the pn node information in the output stream pf.*/
int printNodeAB(FILE* pf, const NodeBT *pn, print_elementtree_function_type f){
  if(!pf || !pn) return ERROR;
  return f(pf,pn->info);
}

/* Writes in the file f the path of a tree in medium order without modifying it */
int tree_inOrder(FILE *f, const Tree *pa){
  if(!f || !pa) return ERROR;
  return tree_inOrderRec(f,pa->root,pa->print_element_function);
}

int tree_inOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p){
  int chars=0;
  if(!f || !pn) return ERROR;
  tree_inOrderRec(f,pn->left,p);
  chars+=printNodeAB(f,pn,p);
  tree_inOrderRec(f,pn->right,p);
  return chars;
}
/* Writes in file f the path of a tree in post order without modifying it. */
int tree_postOrder(FILE *f, const Tree *pa){
  if(!f || !pa) return ERROR;
  return tree_postOrderRec(f,pa->root,pa->print_element_function);
}

int tree_postOrderRec(FILE* f, NodeBT* pn, print_elementtree_function_type p){
  int chars=0;
  if(!f || !pn) return ERROR;
  tree_postOrderRec(f,pn->left,p);
  tree_postOrderRec(f,pn->right,p);
  chars+=printNodeAB(f, pn, p);
  return chars;
}
/* Computes the depth of a tree. An empty tree has depth -1. */
int tree_depth(const Tree *pa){
  if(!pa || tree_isEmpty(pa)==TRUE) return -1;
  return tree_depthRec(pa->root);
}

int tree_depthRec(NodeBT* pn){
    int right_depth=-1,left_depth=-1;
    if(!pn) return -1;
    if(!pn->right && !pn->left) return 0;
    right_depth = 1 + tree_depthRec(pn->right);
    left_depth = 1 + tree_depthRec(pn->left);
    if (right_depth > left_depth){
        return right_depth;
    }
    return left_depth;
}
/* Computes the number of nodes in a tree. An empty tree has 0 nodes.*/
int tree_numNodes(const Tree *pa){
  if(!pa || tree_isEmpty(pa)==TRUE) return 0;
  return tree_numNodesRec(pa->root);
}

int tree_numNodesRec(NodeBT* pn){
  if(!pn) return 0;
  return 1 + tree_numNodesRec(pn->left) + tree_numNodesRec(pn->right);
}
/* Returns TRUE if the element pe can be found in the tree pa */
Bool tree_find(Tree* pa, const void* pe){
  if(!pa || !pe) return FALSE;
  if(lookAB(pa,pe)) return TRUE;
  return FALSE;
}

/*Find an element in a tree. Returns the pointer to the node where the element is or NULL if it does not find it. uses private recursive function*/
NodeBT *lookAB(const Tree *pa, const void* po){
  if(!pa || !po) return NULL;
  return lookABRec(pa->root,po,pa->cmp_element_function);
}

NodeBT *lookABRec(NodeBT* pn, const void* po, cmp_elementtree_function_type c){
  int cmp;
  if(!pn || !po) return NULL;
  cmp=c(po,pn->info);
  if(cmp==0){
    return pn;
  }
  else if(cmp > 0){
    return lookABRec(pn->right,po,c);
  }
  else{
    return lookABRec(pn->left,po,c);
  }
}

int tree_print(FILE* f, Tree* pa){
  int chars=0;
  if(!f || !pa) return ERROR;
  chars+=fprintf(stdout,"Previous order:\n");
  chars+=tree_preOrder(stdout,pa);
  chars+=fprintf(stdout,"\nAverage order:\n");
  chars+=tree_inOrder(stdout,pa);
  chars+=fprintf(stdout,"\nLater order:\n");
  chars+=tree_postOrder(stdout,pa);
  chars+=fprintf(stdout,"\n");
  chars+=tree_printRec(f,pa->root,0,pa->print_element_function);

  return chars;
}

int tree_printRec(FILE* f, NodeBT* pn, int depth, print_elementtree_function_type p){
  int i,chars=0;
  for(i=0;i<depth;i++){
    chars+=fprintf(f,"\t");
  }
  if(!pn){
    chars+=fprintf(stdout,"NULL\n");
    return chars;
  }

  chars+=printNodeAB(f,pn,p);
  chars+=fprintf(f,"\n");
  chars+=tree_printRec(f,pn->left,depth+1,p);
  chars+=tree_printRec(f,pn->right,depth+1,p);
  return chars;
}
