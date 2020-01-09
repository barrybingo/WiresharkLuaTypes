#include "wslua.h"

#ifndef LUAWSTYPES_API
#ifdef _WIN32
#define LUAWSTYPES_API __declspec(dllexport)
#else
#define LUAWSTYPES_API
#endif
#endif

extern int Struct_register(lua_State* L);
extern int UInt64_register(lua_State* L);
extern int Int64_register(lua_State* L);

LUAWSTYPES_API int luaopen_wiresharktypes(lua_State* L) {
    Int64_register(L);
    UInt64_register(L);
    Struct_register(L);
    return 1;
}