TARGET  := zip.library
VERSION := 53

LIBZIPDIR := libzip-1.1.3

CC     := ppc-amigaos-gcc
STRIP  := ppc-amigaos-strip
AR     := ppc-amigaos-ar
RANLIB := ppc-amigaos-ranlib

BUILDSYS := $(shell uname -s)

# Only use host argument if cross-compiling
ifneq ($(BUILDSYS),AmigaOS)
	HOSTARG := --host=ppc-amigaos
else
	HOSTARG := 
endif

CFLAGS  := -O2 -g -Wall -Wwrite-strings -Werror -I./include -I./libzip-build/lib -I./$(LIBZIPDIR)/lib
LDFLAGS := 
LIBS    := 

main_SRCS := $(wildcard main/*.c)
main_OBJS := $(main_SRCS:.c=.o)

OBJS := init.o zlib-stubs.o $(main_OBJS)

STATIC_SRCS := $(wildcard static/*.c)
STATIC_OBJS := $(STATIC_SRCS:.c=.o)

.PHONY: all
all: $(TARGET) libzip.a

libzip-build/Makefile: $(LIBZIPDIR)/configure
	mkdir -p libzip-build
	rm -rf libzip-build/*
	cd libzip-build && ../$(LIBZIPDIR)/configure --prefix=/SDK/local/newlib $(HOSTARG) --disable-shared

.PHONY: build-libzip
build-libzip: libzip-build/Makefile
	$(MAKE) -C libzip-build

init.o: $(TARGET)_rev.h zip_vectors.c zip_vectors.h
$(main_OBJS): zip_vectors.h

$(TARGET): build-libzip $(OBJS)
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $(OBJS) libzip-build/lib/.libs/libzip.a $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

libzip.a: $(STATIC_OBJS)
	$(AR) -crv $@ $^
	$(RANLIB) $@

.PHONY: clean
clean:
	rm -rf libzip-build
	rm -f $(TARGET) $(TARGET).debug *.o main/*.o
	rm -f libzip.a static/*.o

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

