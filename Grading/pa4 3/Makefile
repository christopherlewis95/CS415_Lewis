BIN_PATH = ../bin
SRC_PATH = ../src

CC = mpic++ -std=c++11
DEBUG = -g
CFLAGS = -c -Wall -Wextra -pedantic -L /usr/lib/x86_64-linux-gnu/libpmi.so -lpmi
LFLAGS = -Wall -Wextra -pedantic -L /usr/lib/x86_64-linux-gnu/libpmi.so -lpmi

all: parallel

parallel: timer.o matrix.o generator.o cmath_extra.o
	${CC} ${DEBUG} ${LFLAGS} ${SRC_PATH}/matrix_parallel.cc ${BIN_PATH}/timer.o ${BIN_PATH}/matrix.o ${BIN_PATH}/generator.o ${BIN_PATH}/cmath_extra.o -o ${BIN_PATH}/matrix_parallel

timer.o:
	${CC} ${DEBUG} ${CFLAGS} ${SRC_PATH}/timer.cc -o ${BIN_PATH}/timer.o

matrix.o:
	${CC} ${DEBUG} ${CFLAGS} ${SRC_PATH}/matrix.cc -o ${BIN_PATH}/matrix.o

generator.o:
	${CC} ${DEBUG} ${CFLAGS} ${SRC_PATH}/generator.cc -o ${BIN_PATH}/generator.o

cmath_extra.o:
	${CC} ${DEBUG} ${CFLAGS} ${SRC_PATH}/cmath_extra.cc -o ${BIN_PATH}/cmath_extra.o

clean:
	rm ${BIN_PATH}/*
