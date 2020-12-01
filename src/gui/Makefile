INCLUDE_FOLDER=../include
LINKER_FLAGS=-lSDL2 -lSDL2_ttf
BIN_DIR=../../bin
SRC_DIR=
CC=gcc
CFLAGS=-g
SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o ${BIN_DIR}/gui/$@.o  -c $<

clean:
	rm ${BIN_DIR}/gui/*.o
