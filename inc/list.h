#pragma once

#include <stdatomic.h>

#define secme_list(type) \
struct {                 \
  atomic(type *) next;   \
}

#define secme_list_init(head)                    \
{                                                \
  (head)->next = (__typeof((head)->next))(NULL); \
}

#define secme_list_push(l, p)  \
{                              \
  atomic_store((p)->next, (l)) \
}

#define secme_list_empty(l) {                               \
   __typeof((l)->next tmp__ = NULL;                         \
  (atomic_compare_exchange_weak((l)->next), &tmp__, tmp__); \
}

#define secme_list_pop(l)                             \
({                                                    \
  __typeof((l)->next) res__ = atomic_load((l->next)); \
  if(!secme_list_empty((l))) {                        \
    secme_pop__(l);                                   \
  }                                                   \
  res__;                                              \
})

#define secme_list_pop__(l)                   \
({                                            \
    atomic_store((l)->next, (l)->next->next); \
    atomic_store((l)->next->next, NULL);      \
})

