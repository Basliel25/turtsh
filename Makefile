CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

SRC = main.c builtins.c turtsh.c
OBJ = $(SRC:.c=.o)
TARGET = turtsh

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run: $(TARGET)
	./$(TARGET)
clean: $(TARGET)
	rm -f $(TARGET) $(OBJ)
