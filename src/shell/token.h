
#ifndef LUSH_TOKEN_H
#define LUSH_TOKEN_H

enum Token
{
    LUSH_TOKEN_REGULAR,                // word
    LUSH_TOKEN_SEMICOLON,              // ;
    LUSH_TOKEN_PIPE,                   // |
    LUSH_TOKEN_FORK,                   // &
    LUSH_TOKEN_REDIRECT_STDIN,         // <
    LUSH_TOKEN_REDIRECT_STDOUT,        // >
    LUSH_TOKEN_OR,                     // ||
    LUSH_TOKEN_AND,                    // &&
    LUSH_TOKEN_REDIRECT_STDIN_HEREDOC, // <<
    LUSH_TOKEN_REDIRECT_STDOUT_APPEND, // >>
    LUSH_TOKEN_NEWLINE,
    LUSH_TOKEN_EOF
};

#endif

