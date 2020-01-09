/*
 * wslua.h
 *
 * Wireshark's interface to the Lua Programming Language
 *
 * (c) 2006, Luis E. Garcia Ontanon <luis@ontanon.org>
 * (c) 2007, Tamas Regos <tamas.regos@ericsson.com>
 * (c) 2008, Balint Reczey <balint.reczey@ericsson.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef _PACKET_LUA_H
#define _PACKET_LUA_H

#if defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#if defined(_MSC_VER)

#include "glibtypes.h"

#ifndef g_error

inline void g_error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);

    if (IsDebuggerPresent())
    {
        __debugbreak();
    }      
}
#endif

#endif

#ifndef ws_debug_printf
#define ws_debug_printf     printf
#endif

// Wireshark defines _U_ to mean "Unused" (compiler specific define)
#define _U_ 


/** @file
 * @ingroup wslua_group
 */

#define WSLUA_INIT_ROUTINES "init_routines"
#define WSLUA_PREFS_CHANGED "prefs_changed"


/* type conversion macros - lua_Number is a double, so casting isn't kosher; and
   using Lua's already-available lua_tointeger() and luaL_checkinteger() might be different
   on different machines; so use these instead please! */
#define wslua_togint(L,i)       (gint)            ( lua_tointeger(L,i) )
#define wslua_togint32(L,i)     (gint32)          ( lua_tonumber(L,i) )
#define wslua_togint64(L,i)     (gint64)          ( lua_tonumber(L,i) )
#define wslua_toguint(L,i)      (guint)           ( lua_tointeger(L,i) )
#define wslua_toguint32(L,i)    (guint32)         ( lua_tonumber(L,i) )
#define wslua_toguint64(L,i)    (guint64)         ( lua_tonumber(L,i) )

#define wslua_checkgint(L,i)    (gint)            ( luaL_checkinteger(L,i) )
#define wslua_checkgint32(L,i)  (gint32)          ( luaL_checknumber(L,i) )
#define wslua_checkgint64(L,i)  (gint64)          ( luaL_checknumber(L,i) )
#define wslua_checkguint(L,i)   (guint)           ( luaL_checkinteger(L,i) )
#define wslua_checkguint32(L,i) (guint32)         ( luaL_checknumber(L,i) )
#define wslua_checkguint64(L,i) (guint64)         ( luaL_checknumber(L,i) )

#define wslua_optgint(L,i,d)    (gint)            ( luaL_optinteger(L,i,d) )
#define wslua_optgint32(L,i,d)  (gint32)          ( luaL_optnumber(L,i,d) )
#define wslua_optgint64(L,i,d)  (gint64)          ( luaL_optnumber(L,i,d) )
#define wslua_optguint(L,i,d)   (guint)           ( luaL_optinteger(L,i,d) )
#define wslua_optguint32(L,i,d) (guint32)         ( luaL_optnumber(L,i,d) )
#define wslua_optguint64(L,i,d) (guint64)         ( luaL_optnumber(L,i,d) )



/*
 * toXxx(L,idx) gets a Xxx from an index (Lua Error if fails)
 * checkXxx(L,idx) gets a Xxx from an index after calling check_code (No Lua Error if it fails)
 * pushXxx(L,xxx) pushes an Xxx into the stack
 * isXxx(L,idx) tests whether we have an Xxx at idx
 * shiftXxx(L,idx) removes and returns an Xxx from idx only if it has a type of Xxx, returns NULL otherwise
 * WSLUA_CLASS_DEFINE must be used with a trailing ';'
 * (a dummy typedef is used to be syntactically correct)
 */
#define WSLUA_CLASS_DEFINE(C,check_code) \
    WSLUA_CLASS_DEFINE_BASE(C,check_code,NULL)

#define WSLUA_CLASS_DEFINE_BASE(C,check_code,retval) \
C to##C(lua_State* L, int idx) { \
    C* v = (C*)lua_touserdata (L, idx); \
    if (!v) luaL_error(L, "bad argument %d (%s expected, got %s)", idx, #C, lua_typename(L, lua_type(L, idx))); \
    return v ? *v : retval; \
} \
C check##C(lua_State* L, int idx) { \
    C* p; \
    luaL_checktype(L,idx,LUA_TUSERDATA); \
    p = (C*)luaL_checkudata(L, idx, #C); \
    check_code; \
    return p ? *p : retval; \
} \
C* push##C(lua_State* L, C v) { \
    C* p; \
    luaL_checkstack(L,2,"Unable to grow stack\n"); \
    p = (C*)lua_newuserdata(L,sizeof(C)); *p = v; \
    luaL_getmetatable(L, #C); lua_setmetatable(L, -2); \
    return p; \
}\
gboolean is##C(lua_State* L,int i) { \
    void *p; \
    if(!lua_isuserdata(L,i)) return FALSE; \
    p = lua_touserdata(L, i); \
    lua_getfield(L, LUA_REGISTRYINDEX, #C); \
    if (p == NULL || !lua_getmetatable(L, i) || !lua_rawequal(L, -1, -2)) p=NULL; \
    lua_pop(L, 2); \
    return p ? TRUE : FALSE; \
} \
C shift##C(lua_State* L,int i) { \
    C* p; \
    if(!lua_isuserdata(L,i)) return retval; \
    p = (C*)lua_touserdata(L, i); \
    lua_getfield(L, LUA_REGISTRYINDEX, #C); \
    if (p == NULL || !lua_getmetatable(L, i) || !lua_rawequal(L, -1, -2)) p=NULL; \
    lua_pop(L, 2); \
    if (p) { lua_remove(L,i); return *p; }\
    else return retval;\
} \
typedef int dummy##C

#define WSLUA_TYPEOF_FIELD "__typeof"

/* temporary transition macro to reduce duplication in WSLUA_REGISTER_xxx. */
#define WSLUA_REGISTER_GC(C) \
    luaL_getmetatable(L, #C); \
     /* add the '__gc' metamethod with a C-function named Class__gc */ \
    /* this will force ALL wslua classes to have a Class__gc function defined, which is good */ \
    lua_pushcfunction(L, C ## __gc); \
    lua_setfield(L, -2, "__gc"); \
    /* pop the metatable */ \
    lua_pop(L, 1)

#define __WSLUA_REGISTER_META(C, ATTRS) { \
    const wslua_class C ## _class = { \
        .name               = #C, \
        .instance_meta      = C ## _meta, \
        .attrs              = ATTRS \
    }; \
    wslua_register_classinstance_meta(L, &C ## _class); \
    WSLUA_REGISTER_GC(C); \
}

#define WSLUA_REGISTER_META(C)  __WSLUA_REGISTER_META(C, NULL)
#define WSLUA_REGISTER_META_WITH_ATTRS(C) \
    __WSLUA_REGISTER_META(C, C ## _attributes)

#define __WSLUA_REGISTER_CLASS(C, ATTRS) { \
    const wslua_class C ## _class = { \
        .name               = #C, \
        .class_methods      = C ## _methods, \
        .class_meta         = C ## _meta, \
        .instance_methods   = C ## _methods, \
        .instance_meta      = C ## _meta, \
        .attrs              = ATTRS \
    }; \
    wslua_register_class(L, &C ## _class); \
    WSLUA_REGISTER_GC(C); \
}

#define WSLUA_REGISTER_CLASS(C)  __WSLUA_REGISTER_CLASS(C, NULL)
#define WSLUA_REGISTER_CLASS_WITH_ATTRS(C) \
    __WSLUA_REGISTER_CLASS(C, C ## _attributes)

#define WSLUA_INIT(L) \
    luaL_openlibs(L); \
    wslua_register_classes(L); \
    wslua_register_functions(L);


#define WSLUA_FUNCTION extern int

#define WSLUA_REGISTER_FUNCTION(name)     { lua_pushcfunction(L, wslua_## name); lua_setglobal(L, #name); }

#define WSLUA_REGISTER extern int

#define WSLUA_METHOD static int
#define WSLUA_CONSTRUCTOR static int
#define WSLUA_ATTR_SET static int
#define WSLUA_ATTR_GET static int
#define WSLUA_METAMETHOD static int

#define WSLUA_METHODS static const luaL_Reg
#define WSLUA_META static const luaL_Reg
#define WSLUA_CLASS_FNREG(class,name) { #name, class##_##name }
#define WSLUA_CLASS_FNREG_ALIAS(class,aliasname,name) { #aliasname, class##_##name }
#define WSLUA_CLASS_MTREG(class,name) { "__" #name, class##__##name }

#define WSLUA_ATTRIBUTES static const wslua_attribute_table
/* following are useful macros for the rows in the array created by above */
#define WSLUA_ATTRIBUTE_RWREG(class,name) { #name, class##_get_##name, class##_set_##name }
#define WSLUA_ATTRIBUTE_ROREG(class,name) { #name, class##_get_##name, NULL }
#define WSLUA_ATTRIBUTE_WOREG(class,name) { #name, NULL, class##_set_##name }

#define WSLUA_ATTRIBUTE_FUNC_SETTER(C,field) \
    static int C##_set_##field (lua_State* L) { \
        C obj = check##C (L,1); \
        if (! lua_isfunction(L,-1) ) \
            return luaL_error(L, "%s's attribute `%s' must be a function", #C , #field ); \
        if (obj->field##_ref != LUA_NOREF) \
            /* there was one registered before, remove it */ \
            luaL_unref(L, LUA_REGISTRYINDEX, obj->field##_ref); \
        obj->field##_ref = luaL_ref(L, LUA_REGISTRYINDEX); \
        return 0; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_set_##field

#define WSLUA_ATTRIBUTE_GET(C,name,block) \
    static int C##_get_##name (lua_State* L) { \
        C obj = check##C (L,1); \
        block \
        return 1; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_get_##name

#define WSLUA_ATTRIBUTE_NAMED_BOOLEAN_GETTER(C,name,member) \
    WSLUA_ATTRIBUTE_GET(C,name,{lua_pushboolean(L, obj->member );})

#define WSLUA_ATTRIBUTE_NAMED_NUMBER_GETTER(C,name,member) \
    WSLUA_ATTRIBUTE_GET(C,name,{lua_pushnumber(L,(lua_Number)(obj->member));})

#define WSLUA_ATTRIBUTE_NUMBER_GETTER(C,member) \
    WSLUA_ATTRIBUTE_NAMED_NUMBER_GETTER(C,member,member)

#define WSLUA_ATTRIBUTE_BLOCK_NUMBER_GETTER(C,name,block) \
    WSLUA_ATTRIBUTE_GET(C,name,{lua_pushnumber(L,(lua_Number)(block));})

#define WSLUA_ATTRIBUTE_NAMED_STRING_GETTER(C,name,member) \
    WSLUA_ATTRIBUTE_GET(C,name, { \
        lua_pushstring(L,obj->member); /* this pushes nil if obj->member is null */ \
    })

#define WSLUA_ATTRIBUTE_STRING_GETTER(C,member) \
    WSLUA_ATTRIBUTE_NAMED_STRING_GETTER(C,member,member)

#define WSLUA_ATTRIBUTE_NAMED_OPT_BLOCK_STRING_GETTER(C,name,member,option) \
    WSLUA_ATTRIBUTE_GET(C,name, { \
        char* str;  \
        if ((obj->member) && (obj->member->len > 0)) { \
            if (wtap_block_get_string_option_value(g_array_index(obj->member, wtap_block_t, 0), option, &str) == WTAP_OPTTYPE_SUCCESS) { \
                lua_pushstring(L,str); \
            } \
        } \
    })

/*
 * XXX - we need to support Lua programs getting instances of a "multiple
 * allowed" option other than the first option.
 */
#define WSLUA_ATTRIBUTE_NAMED_OPT_BLOCK_NTH_STRING_GETTER(C,name,member,option) \
    WSLUA_ATTRIBUTE_GET(C,name, { \
        char* str;  \
        if ((obj->member) && (obj->member->len > 0)) { \
            if (wtap_block_get_nth_string_option_value(g_array_index(obj->member, wtap_block_t, 0), option, 0, &str) == WTAP_OPTTYPE_SUCCESS) { \
                lua_pushstring(L,str); \
            } \
        } \
    })

#define WSLUA_ATTRIBUTE_SET(C,name,block) \
    static int C##_set_##name (lua_State* L) { \
        C obj = check##C (L,1); \
        block; \
        return 0; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_set_##name

#define WSLUA_ATTRIBUTE_NAMED_BOOLEAN_SETTER(C,name,member) \
    WSLUA_ATTRIBUTE_SET(C,name, { \
        if (! lua_isboolean(L,-1) ) \
            return luaL_error(L, "%s's attribute `%s' must be a boolean", #C , #name ); \
        obj->member = lua_toboolean(L,-1); \
    })

/* to make this integral-safe, we treat it as int32 and then cast
   Note: This will truncate 64-bit integers (but then Lua itself only has doubles */
#define WSLUA_ATTRIBUTE_NAMED_NUMBER_SETTER(C,name,member,cast) \
    WSLUA_ATTRIBUTE_SET(C,name, { \
        if (! lua_isnumber(L,-1) ) \
            return luaL_error(L, "%s's attribute `%s' must be a number", #C , #name ); \
        obj->member = (cast) wslua_togint32(L,-1); \
    })

#define WSLUA_ATTRIBUTE_NUMBER_SETTER(C,member,cast) \
    WSLUA_ATTRIBUTE_NAMED_NUMBER_SETTER(C,member,member,cast)

#define WSLUA_ATTRIBUTE_NAMED_STRING_SETTER(C,field,member,need_free) \
    static int C##_set_##field (lua_State* L) { \
        C obj = check##C (L,1); \
        gchar* s = NULL; \
        if (lua_isstring(L,-1) || lua_isnil(L,-1)) { \
            s = g_strdup(lua_tostring(L,-1)); \
        } else { \
            return luaL_error(L, "%s's attribute `%s' must be a string or nil", #C , #field ); \
        } \
        if (obj->member != NULL && need_free) \
            g_free((void*) obj->member); \
        obj->member = s; \
        return 0; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_set_##field

#define WSLUA_ATTRIBUTE_STRING_SETTER(C,field,need_free) \
    WSLUA_ATTRIBUTE_NAMED_STRING_SETTER(C,field,field,need_free)

#define WSLUA_ATTRIBUTE_NAMED_OPT_BLOCK_STRING_SETTER(C,field,member,option) \
    static int C##_set_##field (lua_State* L) { \
        C obj = check##C (L,1); \
        gchar* s = NULL; \
        if (lua_isstring(L,-1) || lua_isnil(L,-1)) { \
            s = g_strdup(lua_tostring(L,-1)); \
        } else { \
            return luaL_error(L, "%s's attribute `%s' must be a string or nil", #C , #field ); \
        } \
        if ((obj->member) && (obj->member->len > 0)) { \
            wtap_block_set_string_option_value(g_array_index(obj->member, wtap_block_t, 0), option, s, strlen(s)); \
        } \
        g_free(s); \
        return 0; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_set_##field

#define WSLUA_ATTRIBUTE_NAMED_OPT_BLOCK_NTH_STRING_SETTER(C,field,member,option) \
    static int C##_set_##field (lua_State* L) { \
        C obj = check##C (L,1); \
        gchar* s = NULL; \
        if (lua_isstring(L,-1) || lua_isnil(L,-1)) { \
            s = g_strdup(lua_tostring(L,-1)); \
        } else { \
            return luaL_error(L, "%s's attribute `%s' must be a string or nil", #C , #field ); \
        } \
        if ((obj->member) && (obj->member->len > 0)) { \
            wtap_block_set_nth_string_option_value(g_array_index(obj->member, wtap_block_t, 0), option, 0, s, strlen(s)); \
        } \
        g_free(s); \
        return 0; \
    } \
    /* silly little trick so we can add a semicolon after this macro */ \
    typedef void __dummy##C##_set_##field

#define WSLUA_ERROR(name,error) { luaL_error(L, "%s%s", #name ": " ,error); }
#define WSLUA_ARG_ERROR(name,attr,error) { luaL_argerror(L,WSLUA_ARG_ ## name ## _ ## attr, #name  ": " error); }
#define WSLUA_OPTARG_ERROR(name,attr,error) { luaL_argerror(L,WSLUA_OPTARG_##name##_ ##attr, #name  ": " error); }

#define WSLUA_REG_GLOBAL_BOOL(L,n,v) { lua_pushboolean(L,v); lua_setglobal(L,n); }
#define WSLUA_REG_GLOBAL_STRING(L,n,v) { lua_pushstring(L,v); lua_setglobal(L,n); }
#define WSLUA_REG_GLOBAL_NUMBER(L,n,v) { lua_pushnumber(L,v); lua_setglobal(L,n); }

#define WSLUA_RETURN(i) return (i);

#define WSLUA_API extern

/* empty macro arguments trigger ISO C90 warnings, so do this */
#define NOP (void)p

#define FAIL_ON_NULL(s) if (! *p) luaL_argerror(L,idx,"null " s)

#define FAIL_ON_NULL_OR_EXPIRED(s) if (!*p) { \
        luaL_argerror(L,idx,"null " s); \
    } else if ((*p)->expired) { \
        luaL_argerror(L,idx,"expired " s); \
    }

/* Clears or marks references that connects Lua to Wireshark structures */
#define CLEAR_OUTSTANDING(C, marker, marker_val) void clear_outstanding_##C(void) { \
    while (outstanding_##C->len) { \
        C p = (C)g_ptr_array_remove_index_fast(outstanding_##C,0); \
        if (p) { \
            if (p->marker != marker_val) \
                p->marker = marker_val; \
            else \
                g_free(p); \
        } \
    } \
}

#define WSLUA_CLASS_DECLARE(C) \
extern C to##C(lua_State* L, int idx); \
extern C check##C(lua_State* L, int idx); \
extern C* push##C(lua_State* L, C v); \
extern int C##_register(lua_State* L); \
extern gboolean is##C(lua_State* L,int i); \
extern C shift##C(lua_State* L,int i)


/* Throws a Wireshark exception, catchable via normal exceptions.h routines. */
#define THROW_LUA_ERROR(...) \
    THROW_FORMATTED(DissectorError, __VA_ARGS__)

/* Catches any Wireshark exceptions in code and convert it into a LUA error.
 * Normal restrictions for TRY/CATCH apply, in particular, do not return! */
#define WRAP_NON_LUA_EXCEPTIONS(code) \
{ \
    volatile gboolean has_error = FALSE; \
    TRY { \
        code \
    } CATCH_ALL { \
        lua_pushstring(L, GET_MESSAGE);  \
        has_error = TRUE; \
    } ENDTRY; \
    if (has_error) { lua_error(L); } \
}

typedef struct _wslua_attribute_table {
    const gchar* fieldname;
    lua_CFunction getfunc;
    lua_CFunction setfunc;
} wslua_attribute_table;
extern int wslua_reg_attributes(lua_State* L, const wslua_attribute_table* t, gboolean is_getter);

 /* wslua_internals.c */
 /**
  * @brief Type for defining new classes.
  *
  * A new class is defined as a Lua table type. Instances of this class are
  * created through pushXxx which sets the appropriate metatable.
  */
typedef struct _wslua_class {
    const char* name;                   /**< Class name that is exposed to Lua code. */
    const luaL_Reg* class_methods;      /**< Methods for the static class (optional) */
    const luaL_Reg* class_meta;         /**< Metatable for the static class (optional) */
    const luaL_Reg* instance_methods;   /**< Methods for class instances. (optional) */
    const luaL_Reg* instance_meta;      /**< Metatable for class instances (optional) */
    const wslua_attribute_table* attrs; /**< Table of getters/setters for attributes on class instances (optional). */
} wslua_class;
void wslua_register_classinstance_meta(lua_State* L, const wslua_class* cls_def);
void wslua_register_class(lua_State* L, const wslua_class* cls_def);

extern gboolean wslua_optbool(lua_State* L, int n, gboolean def);

extern const char* wslua_checkstring_only(lua_State* L, int n); 
extern const char* wslua_checklstring_only(lua_State* L, int n, size_t* l);
extern int wslua__concat(lua_State* L);


extern void Int64_pack(lua_State* L, luaL_Buffer* b, gint idx, gboolean asLittleEndian);
extern int Int64_unpack(lua_State* L, const gchar* buff, gboolean asLittleEndian);
extern void UInt64_pack(lua_State* L, luaL_Buffer* b, gint idx, gboolean asLittleEndian);
extern int UInt64_unpack(lua_State* L, const gchar* buff, gboolean asLittleEndian);

extern int wslua_bin2hex(lua_State* L, const guint8* data, const guint len, const gboolean lowercase, const gchar* sep);
extern int wslua_hex2bin(lua_State* L, const char* data, const guint len, const gchar* sep);


#endif