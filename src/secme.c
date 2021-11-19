#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#include "list.h"
#include "session.h"

secme_list(struct secme_session) *sessions;
atomic_bool done = false;

void *producer(void *arg)
{
  struct secme_session session;
  for(size_t i = 0; i < 10; ++i)
  {
    secme_list_push(sessions, &session);
  }

  atomic_store(&done, true);
  (void) arg;
  pthread_exit((void *)0);
}

void *consumer(void *arg)
{
  while(!secme_list_empty(sessions)) {
    secme_list_pop(sessions);
    printf("!\n");
  }

  (void) arg;
  pthread_exit((void *)0);
}

int main(void)
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, producer, NULL);
  pthread_create(&t2, NULL, consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}