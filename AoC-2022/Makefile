CC=gcc
TARGET=aoc-2022

all: $(TARGET)

$(TARGET): aoc-2022.o puzzle01.o puzzle02.o puzzle03.o utils.o
	$(CC) -o $@ $^

aoc-2022.o: aoc-2022.c
	$(CC) -c $^

utils.o: utils.c
	$(CC) -c $^

puzzle01.o: puzzle01.c
	$(CC) -c $^

puzzle02.o: puzzle02.c
	$(CC) -c $^

puzzle03.o: puzzle03.c
	$(CC) -c $^

clean:
	del *.o *.exe

remake: clean all