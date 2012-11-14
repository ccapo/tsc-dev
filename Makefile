SRCDIR = src
INCDIR = include
CPP = g++
UPX = upx -qq

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
	$(UPX) $@

clean:
	rm -f $(OBJS)
	rm -f tsc

all_test: worldmap cavemap cellmap townmap scrollingmap itemlist economy scentmap classtest dictionarytest image2char

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
	$(UPX) $@

scentmap: test/scentmap.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

classtest: test/classtest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

dictionarytest: test/dictionarytest.cpp
	$(CPP) $(CFLAGS) $< -o $@ $(LFLAGS)
	$(UPX) $@

image2char: test/image2char.cpp
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
