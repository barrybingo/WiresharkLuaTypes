# WireSharkLuaTypes src/makefile
#
# Definitions in this section can be overriden on the command line or in the
# environment.
#
# These are equivalent:
#
#    export PLAT=linux DEBUG=DEBUG LUAV_INSTALL=5.2 prefix=/sw
#    make
#
# and
#
#   make PLAT=linux DEBUG=DEBUG LUAV_INSTALL=5.2 prefix=/sw

# PLAT: linux macosx win32 win64 mingw
# platform to build for
PLAT?=linux

# LUAV_INSTALL install path
LUAV_INSTALL?=5.1
# lua version to build against
LUAV_INC?=jit-2.1

# MYCFLAGS: to be set by user if needed
MYCFLAGS?=

# MYLDFLAGS: to be set by user if needed
MYLDFLAGS?=

# DEBUG: NODEBUG DEBUG
# debug mode causes WireSharkLuaTypes to collect and returns timing information useful
# for testing and debugging WireSharkLuaTypes itself
DEBUG?=NODEBUG

# where lua headers are found for macosx builds
# LUAINC_macosx:
# /opt/local/include
LUAINC_macosx_base?=/opt/local/include
LUAINC_macosx?=$(LUAINC_macosx_base)/lua/$(LUAV_INC) $(LUAINC_macosx_base)/lua$(LUAV_INC) $(LUAINC_macosx_base)/lua-$(LUAV_INC)

# FIXME default should this default to fink or to macports?
# What happens when more than one Lua version is installed?
LUAPREFIX_macosx?=/opt/local
CDIR_macosx?=lib/lua/$(LUAV_INSTALL)
LDIR_macosx?=share/lua/$(LUAV_INSTALL)

# LUAINC_linux:
# /usr/include/lua$(LUAV_INSTALL)
# /usr/local/include
# /usr/local/include/lua$(LUAV_INSTALL)
# where lua headers are found for linux builds
LUAINC_linux_base?=/usr/include
LUAINC_linux?=$(LUAINC_linux_base)/lua/$(LUAV_INC) $(LUAINC_linux_base)/lua$(LUAV_INC)
LUAPREFIX_linux?=/usr/local
CDIR_linux?=lib/lua/$(LUAV_INSTALL)
LDIR_linux?=share/lua/$(LUAV_INSTALL)

# LUAINC_freebsd:
# /usr/local/include/lua$(LUAV_INSTALL)
# where lua headers are found for freebsd builds
LUAINC_freebsd_base?=/usr/local/include/
LUAINC_freebsd?=$(LUAINC_freebsd_base)/lua/$(LUAV_INC) $(LUAINC_freebsd_base)/lua$(LUAV_INC)
LUAPREFIX_freebsd?=/usr/local/
CDIR_freebsd?=lib/lua/$(LUAV_INSTALL)
LDIR_freebsd?=share/lua/$(LUAV_INSTALL)

# where lua headers are found for mingw builds
# LUAINC_mingw:
# /opt/local/include
LUAINC_mingw_base?=/usr/include
LUAINC_mingw?=$(LUAINC_mingw_base)/lua/$(LUAV_INC) $(LUAINC_mingw_base)/lua$(LUAV_INC)
LUALIB_mingw_base?=/usr/bin
LUALIB_mingw?=$(LUALIB_mingw_base)/lua/$(LUAV_INSTALL)/lua$(subst .,,$(LUAV_INSTALL)).dll
LUAPREFIX_mingw?=/usr
CDIR_mingw?=lua/$(LUAV_INSTALL)
LDIR_mingw?=lua/$(LUAV_INSTALL)/lua


# LUAINC_win32:
# LUALIB_win32:
# where lua headers and libraries are found for win32 builds
LUAPREFIX_win32?=
LUAINC_win32?=$(LUAPREFIX_win32)/include/lua/$(LUAV_INSTALL) $(LUAPREFIX_win32)/include/lua$(LUAV_INSTALL)
PLATFORM_win32?=Release
CDIR_win32?=bin/lua/$(LUAV_INSTALL)/$(PLATFORM_win32)
LDIR_win32?=bin/lua/$(LUAV_INSTALL)/$(PLATFORM_win32)/lua
LUALIB_win32?=$(LUAPREFIX_win32)/lib/lua/$(LUAV_INSTALL)/$(PLATFORM_win32)
LUALIBNAME_win32?=lua$(subst .,,$(LUAV_INSTALL)).lib

# LUAINC_win64:
# LUALIB_win64:
# where lua headers and libraries are found for win64 builds
LUAPREFIX_win64?=
LUAINC_win64?=$(LUAPREFIX_win64)/include/lua/$(LUAV_INSTALL) $(LUAPREFIX_win64)/include/lua$(LUAV_INSTALL)
PLATFORM_win64?=x64/Release
CDIR_win64?=bin/lua/$(LUAV_INSTALL)/$(PLATFORM_win64)
LDIR_win64?=bin/lua/$(LUAV_INSTALL)/$(PLATFORM_win64)/lua
LUALIB_win64?=$(LUAPREFIX_win64)/lib/lua/$(LUAV_INSTALL)/$(PLATFORM_win64)
LUALIBNAME_win64?=lua$(subst .,,$(LUAV_INSTALL)).lib


# LUAINC_solaris:
LUAINC_solaris_base?=/usr/include
LUAINC_solaris?=$(LUAINC_solaris_base)/lua/$(LUAV_INC) $(LUAINC_solaris_base)/lua$(LUAV_INC)
LUAPREFIX_solaris?=/usr/local
CDIR_solaris?=lib/lua/$(LUAV_INSTALL)
LDIR_solaris?=share/lua/$(LUAV_INSTALL)

# prefix: /usr/local /usr /opt/local /sw
# the top of the default install tree
prefix?=$(LUAPREFIX_$(PLAT))

CDIR?=$(CDIR_$(PLAT))
LDIR?=$(LDIR_$(PLAT))

# DESTDIR: (no default)
# used by package managers to install into a temporary destination
DESTDIR?=

#------
# Definitions below can be overridden on the make command line, but
# shouldn't have to be.


#------
# Install directories
#

INSTALL_DIR=install -d
INSTALL_DATA=install -m644
INSTALL_EXEC=install
INSTALL_TOP=$(DESTDIR)$(prefix)

INSTALL_TOP_LDIR=$(INSTALL_TOP)/$(LDIR)
INSTALL_TOP_CDIR=$(INSTALL_TOP)/$(CDIR)


print:
	@echo PLAT=$(PLAT)
	@echo LUAV_INSTALL=$(LUAV_INSTALL)
	@echo DEBUG=$(DEBUG)
	@echo prefix=$(prefix)
	@echo LUAINC_$(PLAT)=$(LUAINC_$(PLAT))
	@echo LUALIB_$(PLAT)=$(LUALIB_$(PLAT))
	@echo INSTALL_TOP_CDIR=$(INSTALL_TOP_CDIR)
	@echo INSTALL_TOP_LDIR=$(INSTALL_TOP_LDIR)
	@echo CFLAGS=$(CFLAGS)
	@echo LDFLAGS=$(LDFLAGS)

#------
# Supported platforms
#
PLATS= macosx linux win32 win64 mingw solaris

#------
# Compiler and linker settings
# for Mac OS X
SO_macosx=so
O_macosx=o
CC_macosx=gcc
DEF_macosx= -DLUAWSTYPES_$(DEBUG) -DUNIX_HAS_SUN_LEN
CFLAGS_macosx=$(LUAINC:%=-I%) $(DEF) -Wall -O2 -fno-common
LDFLAGS_macosx= -bundle -undefined dynamic_lookup -o
LD_macosx=gcc
WIRESHARKLUATYPES_macosx=wiresharktypes.o

#------
# Compiler and linker settings
# for Linux
SO_linux=so
O_linux=o
CC_linux=gcc
DEF_linux=-DLUAWSTYPES_$(DEBUG) -DLUAWSTYPES_USE_GLIB
CFLAGS_linux=$(LUAINC:%=-I%) $(DEF) -Wall -Wshadow -Wextra \
	-Wimplicit -O2 -ggdb3 -fpic $(shell pkg-config --cflags glib-2.0)
LDFLAGS_linux=-O -shared -fpic $(shell pkg-config --libs glib-2.0) -o
LD_linux=gcc
WIRESHARKLUATYPES_linux=wiresharktypes.o

#------
# Compiler and linker settings
# for FreeBSD
SO_freebsd=so
O_freebsd=o
CC_freebsd=gcc
DEF_freebsd=-DLUAWSTYPES_$(DEBUG) -DUNIX_HAS_SUN_LEN
CFLAGS_freebsd=$(LUAINC:%=-I%) $(DEF) -Wall -Wshadow -Wextra \
	-Wimplicit -O2 -ggdb3 -fpic
LDFLAGS_freebsd=-O -shared -fpic -o
LD_freebsd=gcc
WIRESHARKLUATYPES_freebsd=wiresharktypes.o

#------
# Compiler and linker settings
# for Solaris
SO_solaris=so
O_solaris=o
CC_solaris=gcc
DEF_solaris=-DLUAWSTYPES_$(DEBUG)
CFLAGS_solaris=$(LUAINC:%=-I%) $(DEF) -Wall -Wshadow -Wextra \
	-Wimplicit -O2 -ggdb3 -fpic
LDFLAGS_solaris=-lnsl -lwiresharktypes -lresolv -O -shared -fpic -o
LD_solaris=gcc
WIRESHARKLUATYPES_solaris=wiresharktypes.o

#------
# Compiler and linker settings
# for MingW
SO_mingw=dll
O_mingw=o
CC_mingw=gcc
DEF_mingw= -DLUAWSTYPES_INET_PTON -DLUAWSTYPES_$(DEBUG) \
	-DWINVER=0x0501
CFLAGS_mingw=$(LUAINC:%=-I%) $(DEF) -Wall -O2 -fno-common
LDFLAGS_mingw= $(LUALIB) -shared -Wl,-s -lws2_32 -o
LD_mingw=gcc
WIRESHARKLUATYPES_mingw=wiresharktypes.o


#------
# Compiler and linker settings
# for Win32
SO_win32=dll
O_win32=obj
CC_win32=cl
DEF_win32= //D "WIN32" //D "NDEBUG" //D "_WINDOWS" //D "_USRDLL" \
     //D "_CRT_SECURE_NO_WARNINGS" \
     //D "_WINDLL"  \
     //D "LUAWSTYPES_$(DEBUG)"
CFLAGS_win32=$(LUAINC:%=//I "%") $(DEF) //O2 //Ot //MD //W3 //nologo
LDFLAGS_win32= //nologo //link //NOLOGO //DLL //INCREMENTAL:NO \
    //MANIFEST //MANIFESTFILE:"intermediate.manifest" \
    /MANIFESTUAC:"level='asInvoker' uiAccess='false'" \
	//SUBSYSTEM:WINDOWS //OPT:REF //OPT:ICF //DYNAMICBASE:NO \
    //MACHINE:X86 /LIBPATH:"$(LUALIB)" \
	$(LUALIBNAME_win32) ws2_32.lib //OUT:

LD_win32=cl
WIRESHARKLUATYPES_win32=wiresharktypes.obj

#------
# Compiler and linker settings
# for Win64
SO_win64=dll
O_win64=obj
CC_win64=cl
DEF_win64= //D "WIN32" //D "NDEBUG" //D "_WINDOWS" //D "_USRDLL" \
     //D "_CRT_SECURE_NO_WARNINGS" \
     //D "_WINDLL"  \
     //D "LUAWSTYPES_$(DEBUG)"
CFLAGS_win64=$(LUAINC:%=//I "%") $(DEF) //O2 //Ot //MD //W3 //nologo
LDFLAGS_win64= //nologo //link //NOLOGO //DLL //INCREMENTAL:NO \
    //MANIFEST //MANIFESTFILE:"intermediate.manifest" \
    /MANIFESTUAC:"level='asInvoker' uiAccess='false'" \
	//SUBSYSTEM:WINDOWS //OPT:REF //OPT:ICF //DYNAMICBASE:NO \
    /LIBPATH:"$(LUALIB)" \
	$(LUALIBNAME_win64) ws2_32.lib //OUT:

LD_win64=cl
WIRESHARKLUATYPES_win64=wiresharktypes.obj

.SUFFIXES: .obj

.c.obj:
	$(CC) $(CFLAGS) //Fo"$@" //c $<

#------
# Output file names
#
SO=$(SO_$(PLAT))
O=$(O_$(PLAT))
WIRESHARKLUATYPES_V=0.1-rc1
WIRESHARKLUATYPES_SO=wiresharktypes-$(WIRESHARKLUATYPES_V).$(SO)
UNIX_SO=unix.$(SO)
SOCKET=$(WIRESHARKLUATYPES_$(PLAT))

#------
# Settings selected for platform
#
CC=$(CC_$(PLAT))
DEF=$(DEF_$(PLAT))
CFLAGS=$(MYCFLAGS) $(CFLAGS_$(PLAT))
LDFLAGS=$(MYLDFLAGS) $(LDFLAGS_$(PLAT))
LD=$(LD_$(PLAT))
LUAINC= $(LUAINC_$(PLAT))
LUALIB= $(LUALIB_$(PLAT))

#------
# Modules belonging to wiresharktypes-core
#
WIRESHARKLUATYPES_OBJS= \
	main.$(O) \
	wslua_internals.$(O) \
	wslua_int64.$(O) \
	wslua_struct.$(O)


#------
# Targets
#
default: $(PLAT)


freebsd:
	$(MAKE) all-unix PLAT=freebsd

macosx:
	$(MAKE) all-unix PLAT=macosx

win32:
	$(MAKE) all PLAT=win32

win64:
	$(MAKE) all PLAT=win64

linux:
	$(MAKE) all-unix PLAT=linux

mingw:
	$(MAKE) all PLAT=mingw

solaris:
	$(MAKE) all-unix PLAT=solaris

none:
	@echo "Please run"
	@echo "   make PLATFORM"
	@echo "where PLATFORM is one of these:"
	@echo "   $(PLATS)"

all: $(WIRESHARKLUATYPES_SO)

$(WIRESHARKLUATYPES_SO): $(WIRESHARKLUATYPES_OBJS)
	$(LD) $(WIRESHARKLUATYPES_OBJS) $(LDFLAGS)$@

all-unix: all

$(UNIX_SO): $(UNIX_OBJS)
	$(LD) $(UNIX_OBJS) $(LDFLAGS)$@


install:
	$(INSTALL_DIR) $(INSTALL_TOP_CDIR)
	$(INSTALL_EXEC) $(WIRESHARKLUATYPES_SO) $(INSTALL_TOP_CDIR)/wiresharktypes.$(SO)

install-unix: install
	$(INSTALL_EXEC) $(UNIX_SO) $(INSTALL_WIRESHARKLUATYPES_CDIR)/$(UNIX_SO)

local:
	$(MAKE) install INSTALL_TOP_CDIR=.. INSTALL_TOP_LDIR=..

clean:
	rm -f $(WIRESHARKLUATYPES_OBJS) $(UNIX_SO) $(WIRESHARKLUATYPES_SO)

.PHONY: all $(PLATS) default clean echo none

#------
# List of dependencies
#
main.$(O): wslua.h
wslua_internals.$(O): wslua.h
wslua_int64.$(O): wslua.h
wslua_struct.$(O): wslua.h
