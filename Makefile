TARGET  = zip.library
VERSION = 53

LIBZIPDIR = libzip-1.4.0

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
INCLUDES = -I./include -I./$(LIBZIPDIR)/lib
WARNINGS = -Wall -Wwrite-strings -Werror

CFLAGS  = $(OPTIMIZE) $(DEBUG) $(INCLUDES) $(WARNINGS)
LDFLAGS = -static
LIBS    = 

STRIPFLAGS = -R.comment --strip-unneeded-rel-relocs

main_SRCS = $(wildcard main/*.c)
main_OBJS = $(main_SRCS:.c=.o)

OBJS = init.o zlib-stubs.o bzip2-stubs.o $(main_OBJS)

STATIC_SRCS = $(wildcard static/*.c)
STATIC_OBJS = $(STATIC_SRCS:.c=.o)

.PHONY: all
all: $(TARGET) libzip.a

init.o: $(TARGET)_rev.h zip_vectors.c zip_vectors.h
$(main_OBJS): zip_vectors.h

$(LIBZIPDIR)/libzip.a:
	$(MAKE) -C $(LIBZIPDIR)

$(TARGET): $(OBJS) $(LIBZIPDIR)/libzip.a
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $^ $(LIBS)
	$(STRIP) $(STRIPFLAGS) -o $@ $@.debug

libzip.a: $(STATIC_OBJS)
	$(AR) -crv $@ $^
	$(RANLIB) $@

.PHONY: clean
clean:
	$(MAKE) -C $(LIBZIPDIR) clean
	rm -f $(TARGET) $(TARGET).debug *.o main/*.o
	rm -f libzip.a static/*.o

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

