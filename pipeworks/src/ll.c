#include "ll.h"

#include <stdlib.h>

ll *ll_init()
{
    ll *list = malloc(sizeof(ll));
    atomic_store(&list->size, 0);
    list->first = NULL;
    list->last = NULL;
    return list;
}

void ll_push(ll *list, void *item)
{
    ll_node *last = malloc(sizeof(ll_node));
    last->next = NULL;
    last->value = item;
    last->occupied = 1;

    atomic_fetch_add(&list->size, 1);
    list->last->next = last;
    list->last = last;

    if(list->first == NULL) // Special case
    {
        list->first = list->last;
    }
}

void ll_foreach(ll *list, void(*fn)(void*))
{
    ll_node *node = list->first;
    while(node != NULL)
    {
        if(node->occupied)
            fn(node->value);
        node = node->next;
    }
}

void ll_free(ll *list) // Note: Assumes all values are already free
{
    ll_node *node = list->first;
    while(node != NULL)
    {
        ll_node *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}
