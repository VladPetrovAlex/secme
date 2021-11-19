#pragma once

struct secme_session
{
    int module;
    int action;
    char *args;
    char body[];
};