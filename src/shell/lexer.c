
#include "shell/lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "util/string.h"
#include "shell/token.h"

static void append_until_single_quote(struct String *, FILE *);
static void append_until_double_quote(struct String *, FILE *);

static bool is_whitespace(int);
static bool is_regular(int);

void Lexer_create(struct Lexer *lexer)
{
    // Do nothing
}

void Lexer_delete(struct Lexer *lexer)
{
    // Do nothing
}

void Lexer_get_token(struct Lexer *lexer,
                     enum Token *token,
                     struct String *value,
                     FILE *stream)
{
    int c;

    String_clear(value);

    do
    {
        c = fgetc(stream);

        if (c == '#')
        {
            do
            {
                c = fgetc(stream);
            } while ((c != -1) && (c != '\n'));
        }
    }
    while (is_whitespace(c));

    if (c == -1)
        *token = LUSH_TOKEN_EOF;
    else if (c == '\n')
        *token = LUSH_TOKEN_NEWLINE;
    else if (c == ';')
        *token = LUSH_TOKEN_SEMICOLON;
    else if (c == '|')
    {
        c = fgetc(stream);
        if (c == '|')
            *token = LUSH_TOKEN_OR;
        else
        {
            ungetc(c, stream);
            *token = LUSH_TOKEN_PIPE;
        }
    }
    else if (c == '&')
    {
        c = fgetc(stream);
        if (c == '&')
            *token = LUSH_TOKEN_AND;
        else
        {
            ungetc(c, stream);
            *token = LUSH_TOKEN_FORK;
        }
    }
    else if (c == '<')
    {
        c = fgetc(stream);
        if (c == '<')
            *token = LUSH_TOKEN_REDIRECT_STDIN_HEREDOC;
        else
        {
            ungetc(c, stream);
            *token = LUSH_TOKEN_REDIRECT_STDIN;
        }
    }
    else if (c == '>')
    {
        c = fgetc(stream);
        if (c == '>')
            *token = LUSH_TOKEN_REDIRECT_STDOUT_APPEND;
        else
        {
            ungetc(c, stream);
            *token = LUSH_TOKEN_REDIRECT_STDOUT;
        }
    }
    else
    {
        do
        {
            String_append(value, c);
            if (c == '\'')
                append_until_single_quote(value, stream);
            else if (c == '"')
                append_until_double_quote(value, stream);

            c = fgetc(stream);
        }
        while (is_regular(c));

        ungetc(c, stream);

        *token = LUSH_TOKEN_REGULAR;
    }
}

void append_until_single_quote(struct String *value, FILE *stream)
{
    int c;

    do
    {
        c = fgetc(stream);
        String_append(value, c);
    }
    while (c != '\'');
}

void append_until_double_quote(struct String *value, FILE *stream)
{
    int c;

    do
    {
        c = fgetc(stream);
        String_append(value, c);
    }
    while (c != '"');
}

static bool is_whitespace(int c)
{
    return (c == '\t') || (c == ' ');
}

static bool is_regular(int c)
{
    if (isspace(c) || (c == -1))
        return false;
    if (strchr("#;|&<>", c) != NULL)
        return false;
    return true;
}

