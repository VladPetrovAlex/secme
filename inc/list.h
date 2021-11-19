#pragma once

#include <stdatomic.h>
#include <stddef.h>

#define container_of(p, t, m) ((t *)((char *)(p) - offsetof(t, m)))

struct list_item
{
    struct list_item *_Atomic next;
};

void list_init(struct list_item *list)
{
    list->next = list;
}

void list_push(struct list_item *_Atomic bucket, struct list_item *_Atomic item)
{
    item->next = bucket->next;
    atomic_store(&bucket->next, item);
}

struct list_item * list_pop(struct list_item *_Atomic bucket)
{
    struct list_item *first = atomic_load(&bucket->next);
    if(first != NULL)
    {
        atomic_store(&bucket->next, bucket->next->next);
    }
    return first;
}