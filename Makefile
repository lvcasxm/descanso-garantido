CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I src/include

SRC_DIR = src
MODULES_DIR = src/modulos
INCLUDE_DIR = src/include
BIN_DIR = bin
TEST_DIR = tests/munit

SRC = $(SRC_DIR)/main.c \
      $(wildcard $(MODULES_DIR)/*.c)

OBJ = $(SRC:.c=.o)

APP = $(BIN_DIR)/app

.PHONY: all build clean run

all: build

build: $(APP)

$(APP): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(APP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(APP)

clean:
	rm -rf $(BIN_DIR)/*
	find src -name "*.o" -delete
