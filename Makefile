TARGET  := zip.library
VERSION := 53

CC    := ppc-amigaos-gcc
STRIP := ppc-amigaos-strip
AR    := ppc-amigaos-ar
RM    := rm -f

CFLAGS  := -O2 -g -Wall -Wwrite-strings -Werror -I./include
LDFLAGS := 
LIBS    := 

main_SRCS := $(wildcard main/*.c)
main_OBJS := $(main_SRCS:.c=.o)

OBJS := init.o $(main_OBJS)

STATIC_SRCS := $(wildcard static/*.c)
STATIC_OBJS := $(STATIC_SRCS:.c=.o)

.PHONY: all
all: $(TARGET) libzip.a

$(TARGET): $(OBJS) libzip-1.1.3/libzip.a libz.a
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $^ $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

init.o: $(TARGET)_rev.h zip_vectors.c zip_vectors.h
$(main_OBJS): zip_vectors.h

libzip.a: $(STATIC_OBJS)
	$(AR) -crv $@ $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(TARGET).debug $(OBJS)

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

