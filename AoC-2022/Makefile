CC=gcc
CFLAGS=-Wall -Werror -Wpedantic -g
TARGET=aoc-2022
SRC_FILES=$(wildcard *.c)
OBJ_DIR=build
OBJ_DIR_SENTINEL=$(OBJ_DIR)/.exists
OBJ_FILES=$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c %.h $(OBJ_DIR_SENTINEL)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_SENTINEL):
	mkdir -p $(OBJ_DIR)
	touch $(OBJ_DIR_SENTINEL)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

remake: clean all