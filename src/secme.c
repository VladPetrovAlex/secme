#include <stdio.h>

#include "prod_cons.h"

int main()
{
  typedef struct IntTag
  {
    int v;
    struct IntTag *next;
  } Int;
  
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
  Int cons[] = { 0 };
 
  secme_prod_cons(Int) pc;
  secme_prod_cons_init(&pc);
  
  for(size_t i = 0; i < size; ++i)
  {
    secme_prod_cons_prod(&pc, &prod[i]);
    printf("%d\n", secme_prod_cons_cons(&pc)->v);
  }
  
  (void)cons;
  (void)prod;
  (void)pc;
}
