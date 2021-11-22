#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <string.h>

#include "session.h"
#include "module.h"

#define SCOUNT 10
#define NTHR 8

#if 1

struct wparam
{
    struct list_item sessions;
    pthread_mutex_t mux;
    pthread_cond_t cond;
};

int wparam_init(struct wparam *param)
{
    list_init(&param->sessions);
    if(pthread_mutex_init(&param->mux, NULL))
        return -1;

    if(pthread_cond_init(&param->cond, NULL))
        return -1;

    return 0;
}

void wparam_destroy(struct wparam *param)
{
    pthread_mutex_destroy(&param->mux);
    pthread_cond_destroy(&param->cond);
}

#endif

void *pf(void *arg)
{
    struct wparam *param = arg;
    struct list_item *slist = &param->sessions;

    struct session *sessions = (struct session *)malloc(sizeof(struct session) * SCOUNT);
    
    for(size_t i = 0; i < SCOUNT; ++i)
    {
        list_push(slist, &sessions[i].item);
    }

    pthread_exit((void *)0);
}

void *cf(void *arg)
{
    struct wparam *param = arg;
    struct list_item *slist = &param->sessions;

    int i = 0;
    list_foreach(slist, struct session, item) {
        item->uid = ++i;
        item->sid = ++i;
        printf("(%05d:%05d)\n", item->sid, item->uid);
    }

    pthread_exit((void *)0);
    return NULL;
}

int main()
{
    struct wparam params[NTHR];
    for(size_t i = 0; i < NTHR; ++i)
    {
        wparam_init(&params[i]);
    }

    struct list_item slist = { .next = &slist, };
    
    pthread_t p;
    pthread_t c;
    
    pthread_create(&p, NULL, pf, &params);
    pthread_create(&c, NULL, cf, &params);

    pthread_join(p, NULL);
    pthread_join(c, NULL);
}