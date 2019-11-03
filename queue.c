#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

void queue_initialize(queue* q)
{
    q->first_item = NULL;
    q->last_item = NULL;
    q->size = 0;
}

queue_item* queue_item_allocate(int _password, attComp _complexity)
{
    queue_item* new_item = (queue_item*) malloc(sizeof(queue_item));
    if(new_item != NULL)
    {
        new_item->password = _password;
        new_item->complexity = _complexity;
        new_item->next_item = NULL;
    }
    return new_item;
}

bool queue_add(queue* q, int _password, attComp _complexity)
{
    queue_item* new_item = queue_item_allocate(_password, _complexity);
    if(new_item == NULL)
        return false;

    if(q->first_item == NULL)
        q->first_item = new_item;
    else
        (q->last_item)->next_item = new_item;

    q->last_item = new_item;
    q->size++;
    return true;
}

bool queue_remove(queue* q, int* _password, attComp* _complexity)
{
    if(q->size == 0)
        return false;
    
    queue_item* temp = q->first_item;
    *_password = temp->password;
    *_complexity = temp->complexity;

    q->first_item = q->first_item->next_item;

    free(temp);

    q->size--;
    return true;
}

void queue_clear(queue* q)
{
    q->first_item = NULL;
    q->last_item = NULL;
    q->size = 0;
}


