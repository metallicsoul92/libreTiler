PROJ_NAME=libreTiler
INCLUDE_FOLDER=../include
LINKER_FLAGS=-lSDL2
BIN_DIR=../bin
SRC_DIR=
CC=gcc
CFLAGS=-g


all: ${BIN_DIR}/gui.o ${BIN_DIR}/input.o ${BIN_DIR}/window.o ${BIN_DIR}/main.o
	${CC} ${CFLAGS} ${BIN_DIR}/gui.o ${BIN_DIR}/input.o ${BIN_DIR}/window.o ${BIN_DIR}/main.o ${LINKER_FLAGS} -o ${BIN_DIR}/${PROJ_NAME}

${BIN_DIR}/gui.o: gui.c
	${CC} ${CFLAGS} -I${INCLUDE_FOLDER} -c $< -o $@

${BIN_DIR}/window.o: window.c
	${CC} ${CFLAGS} -I${INCLUDE_FOLDER} -c $< -o $@

${BIN_DIR}/input.o: input.c
	${CC} ${CFLAGS} -I${INCLUDE_FOLDER} -c $< -o $@

${BIN_DIR}/main.o: main.c
	${CC} ${CFLAGS} -I${INCLUDE_FOLDER} -c $< -o $@



clean:
	rm ${BIN_DIR}/*.o
	rm ${BIN_DIR}/${PROJ_NAME}
