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

list_item* list_item_allocate(int _priority, int _entranceTime, int _password, int _complexity)
{
    list_item* new_item = (list_item*) malloc(sizeof(list_item));
    if(new_item != NULL)
    {
        new_item->complexity = _complexity;
        new_item->entranceTime = _entranceTime;
        new_item->password = _password;
        new_item->priority = _priority;
        new_item->next_item = NULL;
    }
    return new_item;
}

bool list_insert_end(list* l, int _priority, int _entranceTime, int _password, int _complexity)
{
    list_item* new_item = list_item_allocate(_priority, _entranceTime,  _password, _complexity);
    if(new_item == NULL)
        return false;

    if(l->size == 0)
        l->first_item = new_item;
    else
    {
        list_item* t = l->first_item;
        list_item* u;
        while(t != NULL)
        {
            u = t;
            t = t->next_item;
        }
        u->next_item = new_item;   
    }
    l->size++;
}

bool list_insert_at(list* l, int _priority, int _entranceTime, int _password, int _complexity, int pos)
{
    list_item* new_item = list_item_allocate(_priority, _entranceTime,  _password, _complexity);
    if(new_item == NULL || pos > (l->size))
        return false;

    list_item* t = l->first_item;
    int i = 0;

    if(pos == 0)
    {
        new_item->next_item = t;
        l->first_item = new_item;
    }
    else
    {
        list_item* u;
        while(i < pos)
        {
            i++;
            u = t;
            t = t->next_item;
        }
        u->next_item = new_item;
        new_item->next_item = t;
    }
    
    l->size++;
    return true;
}

bool list_at(list* l, int* _priority, int* _entranceTime, int* _password, int* _complexity, int pos)
{
    if(pos >= l->size)
        return false;
    else
    {        
        list_item* t = l->first_item;
        int i = 0;
        while (i < pos)
        {
            t = t->next_item;
            i++;
        }
        *_priority = t->priority;
        *_entranceTime = t->entranceTime;
        *_password = t->password;
        *_complexity = t->complexity;    
        return true;    
    }
    
}

bool list_remove_at(list* l, int pos)
{
    if(pos >= l->size)
        return false;
    else
    {      
        if(pos == 0)
        {
            l->first_item = l->first_item->next_item;
            l->size--;
            return true;
        }  

        list_item* t = l->first_item;
        int i = 1;
        while (i < pos)
        {
            t = t->next_item;
            i++;
        }
        t->next_item = t->next_item->next_item;
        l->size--;
        return true;    
    }
}

void list_print(list* l){
    for (int i = 0; i < l->size; i++)
    {
        int a, b, c ,d;
        list_at(&(*l),&a,&b,&c,&d,i);
        printf("cmp: %d | et: %d | pw: %d | pr: %d\n", a,b,c,d);
    }    
}