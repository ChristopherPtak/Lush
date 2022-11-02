
CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
PROJECT(Lush)

##
## Include requirements
##

FIND_PACKAGE(Lua "5.3" REQUIRED)
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})

##
## List of sources
##

INCLUDE_DIRECTORIES(src)
SET(sources
    src/util/memory.c
    src/util/string.c
    src/shell/lexer.c
    src/shell/shell.c
    src/main.c)

##
## Compile and link
##

ADD_EXECUTABLE(lush ${sources})
TARGET_LINK_LIBRARIES(lush ${LUA_LIBRARIES})

