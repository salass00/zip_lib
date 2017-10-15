CC    := ppc-amigaos-gcc
STRIP := ppc-amigaos-strip

CFLAGS  := -O2 -g -Wall -Wwrite-strings -Werror -I/SDK/local/newlib/lib/libzip/include
LDFLAGS := -static
LIBS    := 

.PHONY: all
all: create_zip extract_zip

create_zip: create_zip.o
	$(CC) $(LDFLAGS) -o $@.debug $^ $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

extract_zip: extract_zip.o
	$(CC) $(LDFLAGS) -o $@.debug $^ $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

.PHONY: clean
clean:
	rm -f create_zip extract_zip *.debug *.o

