#pragma once 

#if !defined(MODULE_NAME_STRMAX)
#define MODULE_NAME_STRMAX 20
#endif

struct module
{
    char name[MODULE_NAME_STRMAX + 1];
    void *private;
};