#pragma once

#include <stdatomic.h>

#define secme_prod_cons(type) \
struct {                      \
  atomic(type *) first;       \
  atomic(type *) last;        \
}

#define secme_prod_cons_init(pc)             \
{                                            \
  (pc)->first = (__typeof((pc)->first))(pc); \
  (pc)->last = (__typeof((pc)->last))(pc);   \
}

#define secme_prod_cons_prod(pc, p)    \
{                                      \
  
}

#define secme_prod_cons_empty(pc) \
  (atomic_load((pc)->cons == ))

#define secme_prod_cons_cons(pc)       \
({                                     \
  __typeof((pc)->cons) res__ = NULL;   \
  if(!secme_prod_cons_empty((pc))) {   \
    secme_prod_cons_cons_impl((pc))    \
  }                                    \
  res__;                               \
})

#define secme_prod_cons_cons_impl(pc)  \
({                                     \
  __typeof((pc)->cons) res__ = NULL;   \
  res__ = (pc)->cons->next;            \
  atomic_fetch_sub(&(pc)->count, 1);   \
  res__;                               \
})
