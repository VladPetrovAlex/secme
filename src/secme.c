#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "queue.h"
#include "session.h"

#define SESSION_COUNT 10
atomic_bool ready = false;

void *pf(void *arg)
{ 
  struct secme_queue_item *queue = arg;
  struct secme_session *sessions = malloc(sizeof(*sessions) * SESSION_COUNT);
  
  size_t i = 0;
  for(struct secme_session *session = sessions, *end = session + SESSION_COUNT; session != end; ++session)
  {
    session->module = ++i;
    secme_queue_push(queue, &session->item);   
  }
  
  atomic_store(&ready, true);
  pthread_exit((void *)0);
}

void *cf(void *arg)
{
  struct secme_queue_item *queue = arg;

  while(!atomic_load(&ready))
  {
    printf(".");
  }

  
  printf("%ld", container_of(queue, struct secme_session, item)->module);
  

  atomic_store(&ready, false);
  pthread_exit((void *)0);
}

int main()
{
  struct secme_queue_item sessions;
  secme_queue_init(&sessions);

  pthread_t p;
  pthread_t c;

  pthread_create(&c, NULL, cf, &sessions);
  pthread_create(&p, NULL, pf, &sessions);
  
  pthread_join(p, NULL);
  pthread_join(c, NULL);
}