
#include "util/memory.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
    {
        fprintf(stderr, "lush: Memory allocation failure\n");
        abort();
    }

    return ptr;
}

void *xrealloc(void *ptr, size_t new_size)
{
    void *new_ptr = realloc(ptr, new_size);

    if (new_ptr == NULL)
    {
        fprintf(stderr, "lush: Memory allocation failure\n");
        abort();
    }

    return new_ptr;
}

