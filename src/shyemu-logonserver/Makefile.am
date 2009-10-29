INCLUDES += -I$(srcdir) -I$(srcdir)/../shyemu-shared

bin_PROGRAMS = shyemu-logonserver

shyemu_logonserver_SOURCES = \
	AccountCache.cpp \
	AccountCache.h \
	AuthSocket.cpp \
	AuthSocket.h \
	AuthStructs.h \
	LogonCommServer.cpp \
	LogonCommServer.h \
	LogonConsole.cpp \
	LogonConsole.h \
	LogonOpcodes.cpp \
	LogonOpcodes.h \
	LogonStdAfx.cpp \
	LogonStdAfx.h \
	AutoPatcher.h \
	AutoPatcher.cpp \
	Main.cpp \
	Main.h \
	PeriodicFunctionCall_Thread.h

shyemu_logonserver_LDADD = -lshared -lz
shyemu_logonserver_LDFLAGS = -L$(srcdir)/../shyemu-shared
