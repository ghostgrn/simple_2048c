CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -g
SRC = grid.c game.c
HDR = grid.h
OBJ = $(SRC:.c=.o)
TARGET = 2048c

.PHONY: clean

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ -lm

$(OBJ): $(HDR)
TAGS: $(SRC) $(HDR)
	etags $^
clean:
	rm -f $(TARGET) $(OBJ)
