SRCDIR = src
INCDIR = include
CPP = g++

CFLAGS = -O3 -ffinite-math-only -finline-small-functions -fmove-loop-invariants -foptimize-register-move -foptimize-sibling-calls -freorder-functions -funroll-all-loops -fdata-sections -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND
#CFLAGS = -O3 -ffinite-math-only -finline-small-functions -fmove-loop-invariants -foptimize-register-move -foptimize-sibling-calls -freorder-functions -funroll-all-loops -fdata-sections -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND
#CFLAGS = -O0 -g -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND

# Determine if operating system is 32-bit or 64-bit
TARGET_OS = $(shell uname -m)

# These are the definitions specific to 64-bit systems
ifeq ($(TARGET_OS),x86_64)

	LFLAGS = -Llib/x86_64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/x86_64

else

	LFLAGS = -Llib/i386 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/i386

endif

.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

OBJS = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))

all: tsc

tsc: $(SRCDIR) $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f tsc

all_test: worldmap cavemap cellmap townmap scrollingmap itemlist economy scentmap classtest dictionarytest image2char

worldmap: test/worldmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

cavemap: test/cavemap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

cellmap: test/cellmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

townmap: test/townmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

scrollingmap: test/scrollingmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

itemlist: test/itemlist.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

economy: test/economy.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

scentmap: test/scentmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

classtest: test/classtest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

dictionarytest: test/dictionarytest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

image2char: test/image2char.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)

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
