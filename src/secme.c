#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <string.h>

#include "libcwrap.h"
#include "session.h"
#include "module.h"

struct worker
{
    pthread_t thr;
    pthread_mutex_t mux;
    pthread_cond_t cond;
    void *(*work)(void *);
    struct list_item sessions;
};

int make_worker(struct worker *w, void *(*work)(void *))
{
    if(pthread_cond_init(&w->cond))
        goto cond_fail;

    if(pthread_mutex_init(&w->mux, NULL))
        goto mux_fail;
    
    if(pthread_create(&w->thr, NULL, w->work, w))
        goto thr_fail;

    pthread_mutex_lock(&w->mux);
    pthread_cond_wait(&w->cond, &w->mux);

    list_init(&w->sessions);
    w->work = work;

    return 0;

thr_fail:
    pthread_mutex_destroy(&w->mux);

mux_fail:
    pthread_cond_destroy(&w->cond);

cond_fail:
    // nothing to do

    return -1;
}

int main()
{
    
}