CC      := gcc
CFLAGS  := -Iinclude -Wall -Wextra -O2
SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:.c=.o)
TARGET  := 2DGameEngine

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    LIBS := $(shell pkg-config --libs xcb xcb-util xcb-keysyms)
    CFLAGS += $(shell pkg-config --cflags xcb xcb-util xcb-keysyms)
endif

ifeq ($(UNAME_S), Windows_NT)
    LIBS := -lgdi32
endif

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects and binary
clean:
	rm -f $(OBJ) $(TARGET)
