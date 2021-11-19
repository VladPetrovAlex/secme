#pragma once

struct secme_session
{
    int module;
    int action;
    char *args;
    struct secme_session *next;
    char body[];
};