SRCDIR = src
INCDIR = include
LIBDIR = lib
CPP = g++
UPX = upx -qq

#CFLAGS = -O2 -s -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex
CFLAGS = -O2 -s -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND -DDEV
#CFLAGS = -O0 -g -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND -DDEV

# Determine if operating system is 32-bit or 64-bit
ifeq ($(shell uname -m),x86_64)

	# These are the definitions specific to 64-bit systems
	LFLAGS = -L$(LIBDIR)/x86_64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=$(LIBDIR)/x86_64

else

	# These are the definitions specific to 32-bit systems
	LFLAGS = -L$(LIBDIR)/i386 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=$(LIBDIR)/i386

endif

.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

HEADERS = $(wildcard $(INCDIR)/tsc/*.hpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: tsc

tsc: $(HEADERS) $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $@ $(LFLAGS)
	rm -f $(OBJECTS)
	$(UPX) $@

clean:
	rm -f $(OBJECTS)
	rm -f tsc

all_test: worldmap cavemap cellmap townmap scrollingmap itemlist economy scentmap classtest dictionarytest image2char cavesystem

worldmap: test/worldmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

cavemap: test/cavemap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

cellmap: test/cellmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

townmap: test/townmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

scrollingmap: test/scrollingmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

itemlist: test/itemlist.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

economy: test/economy.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

scentmap: test/scentmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

classtest: test/classtest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

dictionarytest: test/dictionarytest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

image2char: test/image2char.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

cavesystem: test/cavesystem.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

scrollingmenu: test/scrollingmenu.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

clean_test:
	rm -f worldmap
	rm -f cavemap
	rm -f cellmap
	rm -f townmap
	rm -f scrollingmap
	rm -f itemlist
	rm -f economy
	rm -f scentmap
	rm -f classtest
	rm -f dictionarytest
	rm -f image2char
	rm -f cavesystem
	rm -f scrollingmenu
