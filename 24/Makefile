CXX=g++
LD=$(CXX)
CXXFLAGS=-g
LDFLAGS=-g
TARGET=puzzle
OBJ_DIR=build
OBJ_DIR_SENTINEL=$(OBJ_DIR)/.exists

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp %.h $(OBJ_DIR_SENTINEL)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR_SENTINEL):
	mkdir -p $(OBJ_DIR)
	touch $(OBJ_DIR_SENTINEL)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

remake: clean all