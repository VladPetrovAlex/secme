#pragma once

#include <stdatomic.h>

#define secme_list(type) \
struct {                 \
   type *_Atomic next;   \
}

#define secme_list_init(head) atomic_init(head, NULL)

#define secme_list_push(l, p) atomic_store(&(p)->next, (__typeof(p))(l)) 

#define secme_list_empty(l) ({                               \
  __typeof((l)->next) tmp__ = NULL;                          \
  atomic_compare_exchange_strong(&(l)->next, &tmp__, tmp__); \
})

#define secme_list_pop(l)                                                      \
({                                                                             \
  __typeof((l)->next) res__ = atomic_load((__typeof(&(l)->next))&(l)->next);   \
  if(res__ != NULL)                                                            \
  {                                                                            \
    atomic_store((__typeof(&(l)->next))&(l), (__typeof(&(l)->next))(l)->next); \
  }                                                                            \
  res__;                                                                       \
})
