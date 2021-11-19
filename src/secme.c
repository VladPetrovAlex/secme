#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>

#include "session.h"

#define SCOUNT 10

void *pf(void *arg)
{
    struct list_item *_Atomic slist = arg;
    struct session *sessions = (struct session *)malloc(sizeof(struct session) * SCOUNT);
    
    for(size_t i = 0; i < SCOUNT; ++i)
    {
        sessions[i].module = i;
        list_push(slist, &sessions[i].item);
    }

    pthread_exit((void *)0);
}

void *cf(void *arg)
{
    struct list_item *_Atomic slist = arg;
    
    for(struct session *_Atomic s = container_of(slist->next, struct session, item); s->item.next != slist->next; s->item = *s->item.next)
    {
        printf("%ld\n", container_of(list_pop(slist), struct session, item)->module);
    }

    pthread_exit((void *)0);
}

int main()
{
    struct list_item slist = { .next = &slist, };
    
    pthread_t p;
    pthread_t c;
    
    pthread_create(&p, NULL, pf, &slist);
    pthread_create(&c, NULL, cf, &slist);

    pthread_join(p, NULL);
    pthread_join(c, NULL);
}