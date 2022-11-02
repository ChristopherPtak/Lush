
#ifndef LUSH_LEXER_H
#define LUSH_LEXER_H

#include <stdio.h>

#include "util/string.h"
#include "shell/token.h"

struct Lexer
{
    int _placeholder;
};

void Lexer_create(struct Lexer *);
void Lexer_delete(struct Lexer *);

void Lexer_get_token(struct Lexer *, enum Token *, struct String *, FILE *);

#endif

