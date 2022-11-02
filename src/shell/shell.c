
#include "shell/shell.h"

#include <stdbool.h>
#include <stdio.h>

#include <unistd.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "shell/error.h"
#include "shell/token.h"
#include "shell/lexer.h"

static bool file_exists(const char *);
static enum Error run_lua_file(lua_State *, const char *);
static enum Error handle_lua_error(lua_State *, int);

static struct Shell *get_associated_sh(lua_State *);

static int lush_setprompt(lua_State *);

void Shell_create(struct Shell *sh)
{
    sh->L = luaL_newstate();

    luaL_openlibs(sh->L);

    luaL_Reg api[] = {
        {"setprompt", lush_setprompt},
        {NULL, NULL}
    };

    luaL_newlib(sh->L, api);
    lua_setglobal(sh->L, "lush");

    void **associated = lua_getextraspace(sh->L);
    *associated = sh;

    String_create(&sh->lprompt, "lush% ");
}

void Shell_delete(struct Shell *sh)
{
    String_delete(&sh->lprompt);

    lua_close(sh->L);
}

enum Error Shell_load_rcfiles(struct Shell *sh)
{
    if (file_exists(".lushrc"))
        return run_lua_file(sh->L, ".lushrc");
    if (file_exists(".lushrc.lua"))
        return run_lua_file(sh->L, ".lushrc.lua");

    return LUSH_OK;
}

enum Error Shell_run(struct Shell *sh)
{
    struct Lexer lexer;
    struct String value;
    enum Token token;

    Lexer_create(&lexer);
    String_create(&value, NULL);

    do
    {
        printf("%s", String_value(&sh->lprompt));

        do
        {
            Lexer_get_token(&lexer, &token, &value, stdin);
        }
        while (token != LUSH_TOKEN_NEWLINE && token != LUSH_TOKEN_EOF);
    }
    while (token != LUSH_TOKEN_EOF);

    printf("\n");

    String_delete(&value);
    Lexer_delete(&lexer);

    return LUSH_OK;
}

static bool file_exists(const char *path)
{
    return access(path, F_OK) == 0;
}

static enum Error run_lua_file(lua_State *L, const char *path)
{
    int code;

    code = luaL_loadfile(L, path);
    if (code)
        return handle_lua_error(L, code);

    code = lua_pcall(L, 0, 0, 0);
    if (code)
        return handle_lua_error(L, code);

    lua_pop(L, 1);

    return LUSH_OK;
}

static enum Error handle_lua_error(lua_State *L, int code)
{
    int top;

    if (code == 0)
        return LUSH_OK;

    top = lua_gettop(L);

    if (lua_type(L, top) == LUA_TSTRING)
    {
        fprintf(stderr, "lush: %s\n", lua_tostring(L, top));
        lua_pop(L, 1);
    }

    switch (code)
    {
    case LUA_ERRMEM:
        return LUSH_ERROR_LUA_MEMORY;
    case LUA_ERRRUN:
        return LUSH_ERROR_LUA_RUNTIME;
    case LUA_ERRSYNTAX:
        return LUSH_ERROR_LUA_SYNTAX;
    case LUA_ERRERR:
        return LUSH_ERROR_LUA_HANDLER;
    case LUA_ERRFILE:
        return LUSH_ERROR_LUA_OPENFILE;
    }
}

static struct Shell *get_associated_sh(lua_State *L)
{
    struct Shell **associated = lua_getextraspace(L);
    return *associated;
}

static int lush_setprompt(lua_State *L)
{
    struct Shell *sh = get_associated_sh(L);
    const char *value = luaL_checkstring(L, 1);

    String_set(&sh->lprompt, value);

    return 0;
}

