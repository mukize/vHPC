# Usage:
#   make              – build
#   make install      – install executable + headers
#   make uninstall    – remove them
#   make clean        – wipe build artefacts

TARGET   = vhpc
SRCS     = $(wildcard src/*.c)
OBJS     = $(SRCS:.c=.o)
INCLUDES = $(wildcard include/*.h)

PREFIX  ?= /usr/local
BINDIR   = $(PREFIX)/bin
INCDIR   = $(PREFIX)/include/$(TARGET)

# CFLAGS ?= -Wall -Wextra -g
CFLAGS += -Iinclude

LDFLAGS += -lraylib -lm

# Build rules
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

# Install/uninstall
install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)

clean:
	rm -rf build $(TARGET)

.PHONY: install uninstall clean
