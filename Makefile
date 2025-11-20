BIN = ./bin
SRC = ./src

SRCS = $(shell find $(SRC) -name "*.c")
OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP -g
LD = -lm

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	LD += -lX11
endif

$(BIN):
	mkdir $@

dirs: $(BIN)

$(OBJS) : $(BIN)/%.o : $(SRC)/%.c | dirs
	 $(CC) $(CFLAGS) -c $< -o $@

$(BIN)/ezk_window.o : $(BIN)/ezk_bflag.o

window: $(BIN)/ezk_bflag.o $(BIN)/ezk_window.o 
	$(CC) -o $(BIN)/window  ./tests/window_test.c $^ $(LD) -g

-include $(wildcard $(BIN)/*.d)

clean: 
	rm -rf $(BIN)/
	rm -rf $(SRC)/*.gch
