#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "link.h"

int main(){
  Link *l=NULL;
  l=link_create(1);
  if(!l) return -1;
  link_set_name(l,"Link 1");
  link_set_space1(l,1);
  link_set_space2(l,2);
  link_set_status(l,TRUE);
  link_print(l);
  link_destroy(l);
  return 0;
}
