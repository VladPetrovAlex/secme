#pragma once

#include <stdatomic.h>

#define secme_prod_cons(type) \
struct {                      \
  type *cons;                 \
  type *prod;                 \
  atomic_size_t count;        \
}

#define secme_prod_cons_init(pc) \
{                                \
  __typeof(*(pc)->cons) init__;  \
  (pc)->cons = &init__;           \
  (pc)->prod = &init__;           \
  (pc)->count = 0;               \
}

#define secme_prod_cons_prod(pc, p)  \
{                                    \
  (pc)->prod->next = p;              \
  (pc)->prod = p;                    \
  atomic_fetch_add(&(pc)->count, 1); \
}

#define secme_prod_cons_cons(pc)                 \
({                                               \
  __typeof((pc)->cons) res__ = (pc)->cons->next; \
  (pc)->cons = (pc)->cons->next;                 \
  atomic_fetch_sub(&(pc)->count, 1);             \
  res__;                                         \
})
