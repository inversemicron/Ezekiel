BIN = ./bin
BUILD = ./build
LIB = ./lib
SRC = ./src
TST = ./tst
PREFIX = ezk

CC = gcc
AR = ar
CFLAGS ?= -Wall -Wextra -Wpedantic -O2 -MMD -MP -g -fPIC
LDFLAGS = -lm

ifndef OS
UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(UNAME_S),Linux)
OS := linux
SOEXT := so
LDFLAGS += -lX11
else ifeq ($(UNAME_S),Darwin)
OS := macos
SOEXT := dylib
else ifeq ($(OS),Windows_NT)
OS := windows
SOEXT = dll
else
OS := unknown
endif
endif # OS

SRC_C := $(shell find $(SRC) -maxdepth 1 -name '*.c')
SRC_MOD_C := $(shell find $(SRC) -mindepth 2 -maxdepth 2 -name '*.c' ! -name '*_internal.c')
SRC_INT_C := $(shell find $(SRC) -mindepth 3 -name '*_internal.c' | grep '/$(OS)/')

OBJ := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRC_C) $(SRC_MOD_C) $(SRC_INT_C))

TST_SRC = $(shell find $(TST) -name '*_test.c')
TST_BIN = $(patsubst $(TST)/%.c,$(BIN)/%,$(TST_SRC))

LIB_NAME    := lib$(PREFIX).$(SOEXT)
LIB_TARGET  := $(LIB)/$(LIB_NAME)

all: dirs $(LIB_TARGET) tests

dirs:
	@mkdir -p $(BIN) $(BUILD) $(LIB)

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TARGET): $(OBJ)
	$(CC) -shared $^ -o $@ $(LDFLAGS) -g

$(BIN)/%: $(TST)/%.c $(LIB_TARGET)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -L$(LIB) -l$(PREFIX) $(LDFLAGS) -o $@

tests: $(TST_BIN)

clean:
	@echo $(OBJ)
	rm -rf $(BUILD) $(BIN) $(LIB)

window: tests
	./bin/window_test

.PHONY: all clean tests dirs
-include $(shell find $(BIN) -name '*.d' 2>/dev/null)
