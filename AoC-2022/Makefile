CC=gcc
TARGET=aoc-2022
SRC_FILES=$(wildcard *.c)
OBJ_DIR=build
OBJ_FILES=$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.c create_dir
	$(CC) -c $< -o $@

create_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET).exe

remake: clean all