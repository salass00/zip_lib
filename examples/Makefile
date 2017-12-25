CC    = ppc-amigaos-gcc
STRIP = ppc-amigaos-strip

OPTIMIZE = -O2
DEBUG    = -g
WARNINGS = -Wall -Wwrite-strings -Werror

CFLAGS  = $(OPTIMIZE) $(DEBUG) $(WARNINGS)
LDFLAGS = -static
LIBS    = 

STRIPFLAGS = -R.comment --strip-unneeded-rel-relocs

.PHONY: all
all: create_zip extract_zip

create_zip: create_zip.o
	$(CC) $(LDFLAGS) -o $@.debug $^ $(LIBS)
	$(STRIP) $(STRIPFLAGS) -o $@ $@.debug

extract_zip: extract_zip.o
	$(CC) $(LDFLAGS) -o $@.debug $^ $(LIBS)
	$(STRIP) $(STRIPFLAGS) -o $@ $@.debug

.PHONY: clean
clean:
	rm -f create_zip extract_zip *.debug *.o

