TARGET  = zip.library
VERSION = 54

LIBZIPDIR = libzip-1.9.2

CC     = ppc-amigaos-gcc
STRIP  = ppc-amigaos-strip
AR     = ppc-amigaos-ar
RANLIB = ppc-amigaos-ranlib

BUILDSYS = $(shell uname -s)

# Only use host argument if cross-compiling
ifneq ($(BUILDSYS),AmigaOS)
	HOSTARG = --host=ppc-amigaos
else
	HOSTARG = 
endif

OPTIMIZE = -O2 -fomit-frame-pointer
DEBUG    = -g
INCLUDES = -I./include -I. -I./$(LIBZIPDIR) -I./$(LIBZIPDIR)/lib
WARNINGS = -Wall -Wwrite-strings -Werror

CFLAGS  = $(OPTIMIZE) $(DEBUG) $(INCLUDES) $(WARNINGS)
LDFLAGS = -static
LIBS    = 

STRIPFLAGS = -R.comment --strip-unneeded-rel-relocs

main_SRCS = $(wildcard main/*.c)
main_OBJS = $(main_SRCS:.c=.o)

OBJS = init.o zlib-stubs.o bzip2-stubs.o lzma-stubs.o amissl-stubs.o $(main_OBJS)

STATIC_SRCS = $(wildcard static/*.c)
STATIC_OBJS = $(STATIC_SRCS:.c=.o)

.PHONY: all
all: compile-libzip $(TARGET) libzip.a compile-examples

amissl-stubs.o: WARNINGS += -Wno-deprecated-declarations

init.o: $(TARGET)_rev.h zip_vectors.c zip_vectors.h
$(main_OBJS): zip_vectors.h

.PHONY: compile-libzip
compile-libzip:
	$(MAKE) -C $(LIBZIPDIR)

$(LIBZIPDIR)/libzip.a: compile-libzip
	@true

$(TARGET): $(OBJS) $(LIBZIPDIR)/libzip.a
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $^ $(LIBS)
	$(STRIP) $(STRIPFLAGS) -o $@ $@.debug

libzip.a: $(STATIC_OBJS)
	$(AR) -crv $@ $^
	$(RANLIB) $@

.PHONY: compile-examples
compile-examples:
	$(MAKE) -C examples

.PHONY: clean
clean:
	$(MAKE) -C $(LIBZIPDIR) clean
	rm -f $(TARGET) $(TARGET).debug *.o main/*.o
	rm -f libzip.a static/*.o
	$(MAKE) -C examples clean

.PHONY: revision
revision:
	bumprev -e si $(VERSION) $(TARGET)

