
#ifndef LUSH_SHELL_H
#define LUSH_SHELL_H

#include <lua.h>

#include "util/string.h"
#include "shell/error.h"

struct Shell
{
    lua_State *L;

    struct String lprompt;
};

void Shell_create(struct Shell *);
void Shell_delete(struct Shell *);

enum Error Shell_load_rcfiles(struct Shell *);
enum Error Shell_run(struct Shell *);

#endif

