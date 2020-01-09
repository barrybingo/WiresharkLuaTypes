# luasocket makefile
#
# see src/makefile for description of how to customize the build
#
# Targets:
#   install            install system independent support
#   install-unix           also install unix-only support
#   install-both       install for lua51 lua52 lua53
#   install-both-unix      also install unix-only
#   print	           print the build settings

PLAT?= linux
PLATS= macosx linux win32 win64 mingw freebsd solaris
LUAV?=luajit-2.0
LUABIN?=/usr/bin/luajit-2.1.0-beta3

all: $(PLAT)

$(PLATS) none install install-unix local clean:
	$(MAKE) -C src $@

print:
	$(MAKE) -C src $@

test:
	cd test && $(LUABIN) testrunner.lua

install-both:
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.1
	@cd src; $(MAKE) install LUAV=5.1
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.2
	@cd src; $(MAKE) install LUAV=5.2
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.3
	@cd src; $(MAKE) install LUAV=5.3

install-both-unix:
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.1
	@cd src; $(MAKE) install-unix LUAV=5.1
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.2
	@cd src; $(MAKE) install-unix LUAV=5.2
	$(MAKE) clean
	@cd src; $(MAKE) $(PLAT) LUAV=5.3
	@cd src; $(MAKE) install-unix LUAV=5.3

.PHONY: test

