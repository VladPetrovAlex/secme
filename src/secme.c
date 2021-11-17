#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "prod_cons.h"

#define PROD_ROUNDS 10
#define PROD_MAX 1000

typedef struct IntTag
{
  int v;
  struct IntTag *next;
} Int;

secme_prod_cons(Int) gInts;
atomic_bool complete = false;

void *producer(void *arg)
{
  for(size_t i = 0; i < PROD_ROUNDS; ++i)
  {
    srand(time(NULL));
    int part_size = rand() % PROD_MAX;
    for(size_t i = 0; i < part_size; ++i)
    {
      Int product = { i, NULL, }
      secme_prod_cons_prod(gInts, &product);
    }
    sleep(1);
  }
  
  atomic_store(&complete, true);
}

void *consumer(void *arg)
{
  while(secme)
}

int main()
{
  secme_prod_cons_init(&gInts);
  
  
  
  
  Int prod[] = {
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
  };
  
  size_t size = sizeof(prod) / sizeof(prod[0]);
 
  secme_prod_cons(Int) pc;
  secme_prod_cons_init(&pc);
  
  for(size_t i = 0; i < size; ++i)
  {
    secme_prod_cons_prod(&pc, &prod[i]);
    printf("(%lu)\n", secme_prod_cons_count(&pc));
  }
  
  (void)prod;
  (void)pc;
}
