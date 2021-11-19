#pragma once

#include "list.h"
#include "module.h"

typedef  int (*module_action)(char *);

struct session
{
    int sid;
    int uid;
    size_t flags;
    struct list_item item;
    struct list_item in;
    struct list_item out;
};

int make_session(struct session *session, int sid, int uid)
{
    session->sid = sid;
    session->uid = uid;
    session->flags = 0;
    list_init(&session->item);
    list_init(&session->in);
    list_init(&session->out);
    
    return 0;
}