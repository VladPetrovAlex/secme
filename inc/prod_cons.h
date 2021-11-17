#pragma once

#include <stdatomic.h>

#define secme_prod_cons(type) \
struct {                      \
  type *cons;                 \
  type *prod;                 \
  atomic_size_t count;        \
}

#define secme_prod_cons_init(pc)           \
{                                          \
  (pc)->cons = (__typeof((pc)->cons))(pc); \
  (pc)->prod = (__typeof((pc)->prod))(pc); \
  (pc)->count = 0;                         \
}

#define secme_prod_cons_prod(pc, p)    \
{                                      \
  (pc)->prod = (pc)->prod->next = (p); \
  atomic_fetch_add(&(pc)->count, 1);   \
}

#define secme_prod_cons_count(pc) \
  (atomic_load(&(pc)->count))

#define secme_prod_cons_empty(pc) \
  (0 == secme_prod_cons_count((pc)))

#define secme_prod_cons_cons(pc)       \
({                                     \
  __typeof((pc)->cons) res__ = NULL;   \
  if(!secme_prod_cons_empty((pc))) {   \
    res__ = (pc)->cons->next;          \
    atomic_fetch_sub(&(pc)->count, 1); \
  }                                    \
  res__;                               \
})
