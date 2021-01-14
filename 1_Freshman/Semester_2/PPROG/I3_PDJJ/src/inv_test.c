#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "inventory.h"
#include "set.h"

int main(){

Bag *bag;
Id id1=1, id2=2;
int max_obj=5;

bag=bag_create();

bag_setMaxObj(bag, max_obj);

bag_addObj(bag, id1);
bag_addObj(bag, id2);

bag_print(bag);

bag_destroy(bag);

return 0;
}
