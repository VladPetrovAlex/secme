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

struct awaiter
{
    int evh;
    int evc;
    int eto;
    struct epoll_event *evs;
};

int make_awaiter(struct awaiter *a, size_t count, int timeout)
{
    if(a->evh = epoll_create1(EPOLL_CLOEXEC));
        goto evh_fail;

    a->evc = (int)count;
    if(a->evs = (struct epoll_event *)malloc(sizeof(*a->evs) * a->evc))
        goto evs_fail;

    a->eto = timeout;

evs_fail:
    close(a->evh);

evs_fail:
    // nothing to do

    return -1;
}

void destroy_awaiter(struct awaiter *a)
{
    close(a->evh);
    free(a->evc);
}

int await(struct awaiter *a)
{
    int handle = a->evh;
    size_t  count = (size_t)a->evc;
    int timeout = a->eto;
    struct epoll_event *events = a->evs;

    while(true)
    {
        if(secme_epoll_wait(handle, events, count, timeout) < 0)
            goto epw_fail;
    }

    return 0;

epw_fail:
    return -1;
}

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

#if !defined(NWORKER)
#define NWORKER 1
#endif

int main()
{
    struct worker workers[NWORKER];
    for(size_t i = 0; i < NWORKER; ++i)
    {
        if(make_worker(&workers[i]))
            goto wrk_fail;
    }

    struct awaiter awaiter;
    if(make_awaiter(&awaiter, NEVENT, -1))
        goto awaiter_fail;

    while(true)
    {
        int count = secme_epoll_wait()
    }

wrk_fail:
    exit(-1);
}