#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"
/*main that checks if set moduel is correct*/
int main(){
Dialogue *dial=NULL;
if(!(dial=dial_create())){
  printf("Error creating dialogue\n");
}
printf("%s\n",dial_get_sentence(dial,"Unknown"));
printf("%s\n",dial_get_sentence(dial,"Next:ERROR"));
printf("%s\n",dial_get_sentence(dial,"Next:ERROR"));
printf("%s\n",dial_get_sentence(dial,"Inspect:ERROR"));
printf("%s\n",dial_get_sentence(dial,"Inspect:OK"));
dial_destroy(dial);
return 0;
}
