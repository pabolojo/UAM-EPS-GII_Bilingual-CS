#include "list.h"
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainCleanUp (int ret_value, List *pl1, List *pl2,int *pe)
{
   list_destroy(pl1);
   list_destroy(pl2);
   free(pe);
   exit(ret_value);

}
int main(int argc, char** argv)
{
/*variable declaration*/
List *pl1=NULL;
List *pl2=NULL;
int number1=0;
int *pe=NULL,ret_value=EXIT_FAILURE;
int i;
if(argc!=2){
  printf("Execution command should be like: %s <integer>\n",argv[0]);
  return ERROR;
}
pl1=list_ini(int_destroy,int_copy,int_print,int_cmp);
pl2=list_ini(int_destroy,int_copy,int_print,int_cmp);
pe=int_ini();
if(!pl1||!pl2||!pe)
{
  printf("Error initializing lists\n");
  mainCleanUp(ret_value,pl1,pl2,pe);
}

/*values of the variables as arguments */
number1=atoi(argv[1]);
for(i=number1;i>0;i--)
{
  pe=int_setInfo(pe,i);
 if((i%2)==0)
   {
     if(list_insertFirst(pl1,pe)==ERROR){
       printf("Error inserting element at the beginning of list1\n");
       mainCleanUp(ret_value,pl1,pl2,pe);
     }
   }
 else
   {
     if(list_insertLast(pl1,pe)==ERROR){
       printf("Error inserting element at the end of list1\n");
       mainCleanUp(ret_value,pl1,pl2,pe);
     }
   }
   if(list_insertInOrder(pl2,pe)==ERROR){
     printf("Error inserting element in order in list2\n");
     mainCleanUp(ret_value,pl1,pl2,pe);
   }
}
list_print(stdout,pl1);
list_print(stdout,pl2);
mainCleanUp(EXIT_SUCCESS,pl1,pl2,pe);
return 0;


}
