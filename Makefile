CC=gcc
FLAGS=-Wall -D NDEBUG
SRC=touch.c
HDR=touch.h

all: touch

touch: $(SRC) $(HDR)
	$(CC) $(FLAGS) $(SRC) $(HDR) -o touch