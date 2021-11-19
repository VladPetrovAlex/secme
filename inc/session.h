#pragma once

#include "queue.h"

struct secme_session
{
    struct secme_queue_item item;
    size_t module;
};