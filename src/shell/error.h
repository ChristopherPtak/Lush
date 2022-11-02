
#ifndef LUSH_UTILS_ERROR_H
#define LUSH_UTILS_ERROR_H

enum Error
{
    LUSH_OK = 0,

    // All errors that could be returned by Lua
    LUSH_ERROR_LUA_MEMORY,
    LUSH_ERROR_LUA_RUNTIME,
    LUSH_ERROR_LUA_SYNTAX,
    LUSH_ERROR_LUA_HANDLER,
    LUSH_ERROR_LUA_OPENFILE
};

#endif

