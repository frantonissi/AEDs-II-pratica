CC = gcc
CFLAGS = -Wall -g -std=c99
DEPS = sorting.h
OBJ = main.o sorting.o
TARGET = sorter

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c main.c

sorting.o: sorting.c $(DEPS)
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f $(OBJ) $(TARGET)