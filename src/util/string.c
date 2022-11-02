
#include "util/string.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "util/memory.h"

#define INITIAL_CAPACITY 16

void String_create(struct String *s, const char *value)
{
    s->buffer = xmalloc(INITIAL_CAPACITY);
    s->size = 0;
    s->cap = INITIAL_CAPACITY;

    if (value != NULL)
        String_set(s, value);
    else
        String_clear(s);
}

void String_delete(struct String *s)
{
    free(s->buffer);
}

void String_clear(struct String *s)
{
    s->size = 0;
    s->buffer[0] = '\0';
}

void String_set(struct String *s, const char *value)
{
    size_t new_size = strlen(value);
    size_t new_cap = new_size + 1;

    if (new_cap > s->cap)
    {
        s->buffer = xrealloc(s->buffer, new_cap);
        s->cap = new_cap;
    }

    strcpy(s->buffer, value);
    s->size = new_size;
}

void String_append(struct String *s, char c)
{
    size_t new_size = s->size + 1;

    if (new_size == s->cap)
    {
        size_t new_cap = s->cap * 2;
        s->buffer = xrealloc(s->buffer, new_cap);
        s->cap = new_cap;
    }

    s->buffer[s->size] = c;
    s->buffer[s->size + 1] = 0;
    s->size += 1;
}

const char *String_value(const struct String *s)
{
    return s->buffer;
}

