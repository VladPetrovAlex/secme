#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"
#include "session.h"

atomic_bool done = false;

void *producer(void *arg)
{
  struct secme_session *_Atomic sessions = arg;
  printf("d: %ld\n", (size_t)sessions);
  
  for(size_t i = 1; i < 11; ++i)
  {
    struct secme_session *_Atomic session = (struct secme_session *)malloc(sizeof(struct secme_session));
    secme_list_push(sessions, session);
    printf("d: %ld\n", (size_t)sessions);
  }

  atomic_store(&done, true);
  pthread_exit((void *)0);
}

void *consumer(void *arg)
{
  struct secme_session *_Atomic sessions = arg;
  // printf("c: %p\n", sessions);
  
  secme_list_pop(sessions);
  atomic_store(&done, false);
  (void)arg;
  pthread_exit((void *)0);
}

int main(void)
{
  secme_list(struct secme_session) *_Atomic sessions = (__typeof(sessions))malloc(sizeof(*sessions));
  
  pthread_t t1;
  pthread_t t2;
  pthread_create(&t1, NULL, producer, sessions);
  sleep(2);
  pthread_create(&t2, NULL, consumer, sessions);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}