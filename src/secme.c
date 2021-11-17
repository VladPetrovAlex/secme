#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "prod_cons.h"

#define PROD_ROUNDS 10U
#define PROD_MAX 10U

typedef struct IntTag
{
  int v;
  struct IntTag *next;
} Int;

secme_prod_cons(Int) gInts;
atomic_bool complete = false;

void *producer(void *arg)
{
  atomic_store(&complete, false);
  
  for(size_t i = 0; i < PROD_ROUNDS; ++i)
  {
    srand(time(NULL));
    size_t part_size = PROD_MAX;
    for(size_t i = 0; i < part_size; ++i)
    {
      Int product = { i, NULL, };
      secme_prod_cons_prod(&gInts, &product);
    }
  }
  
  atomic_store(&complete, true);
  pthread_exit((void *)0);
  (void)arg;
}

void *consumer(void *arg)
{
  size_t count = 0;
  
  while(!atomic_load(&complete))
  {
    if(secme_prod_cons_cons(&gInts) != NULL)
    {
      ++count;
    }
  }
  
  printf("%lu\n", count);
  pthread_exit(arg);
}

int main()
{
  secme_prod_cons_init(&gInts);
  pthread_t ct, pt;
  
  pthread_create(&pt, NULL, producer, NULL);
  sleep(1);
  pthread_create(&ct, NULL, consumer, NULL);
  
  pthread_join(ct, NULL);
  pthread_join(pt, NULL);
  
  return 0;
}
