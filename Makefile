BIN = ./bin
SRC = ./src

SRCS = $(shell find $(SRC) -name "*.c")
OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)

GCC = gcc
LD = -lm # not actually needed

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	LD += -lX11
endif

$(BIN):
	mkdir $@

dirs: $(BIN)

$(OBJS) : $(BIN)/%.o : $(SRC)/%.c
	gcc -c $< -o $@ -MMD -g

window: dirs $(BIN)/ezk_window.o
	gcc ./tests/window_test.c $(BIN)/ezk_window.o -o $(BIN)/win_test $(LD) -g

clean: 
	rm -rf $(BIN)/
	rm -rf $(SRC)/*.gch
