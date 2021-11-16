#pragma once

union secme_sockaddr
{
  struct sockaddr base;
  struct sockaddr_in v4;
  struct sockaddr_in6 v6;
};

struct secme_netsession_id
{
  secme_sid sid;
  secme_uid uid;
};

struct secme_worker
{
  pthread_t thr;
  QUEUE(struct secme_work) works;
  pthread_mutex_t mux;
  pthread_cond_t cond;
};

struct secme_netsession
{
  int sock;
  union secme_sockaddr addr;
  struct secme_worker *worker;
  struct secme_netsession_id;
};