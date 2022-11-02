
#ifndef LUSH_UTILS_STRING_H
#define LUSH_UTILS_STRING_H

#include <stddef.h>

struct String
{
    char *buffer;
    size_t size;
    size_t cap;
};

void String_create(struct String *, const char *);
void String_delete(struct String *);

void String_clear(struct String *);
void String_set(struct String *, const char *);
void String_append(struct String *, char);

const char *String_value(const struct String *);

#endif

