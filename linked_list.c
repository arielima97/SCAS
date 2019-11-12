#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

void list_initialize(list* l)
{
    l->first_item = NULL;
    l->size = 0;
    l->isPriority = false;
    l->estimatedTime = 0;
    l->stopType = 0;
    l->periodLastStop = 0;
}
