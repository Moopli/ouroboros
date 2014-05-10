#ifndef LUAEXPOSE_H_INCLUDED
#define LUAEXPOSE_H_INCLUDED
#include "lualib/luainclude.h"

int initLua();
static int latticeWrapper(lua_State *L);

#endif // LUAEXPOSE_H_INCLUDED
