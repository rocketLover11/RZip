# --- Config ---
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2 -g
TARGET = rzip
SRCDIR = src
BUILDDIR = build
# --------------

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

all: $(BUILDDIR) $(TARGET) $(LINK)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LINK):
	$(CC) -o $(TARGET) build/main.o

.PHONY: all clean

clean:
	del /q /f build