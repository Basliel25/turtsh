CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

SRC = $(wildcard src/*.c src/Builtins/*.c src/Parser/*.c)
OBJ = $(SRC:.c=.o)
TARGET = turtsh

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -DDEBUG -fsanitize=address
debug: $(TARGET)

# test: $(TEST)
#	./$(TARGET)
run: $(TARGET)
	./$(TARGET)
clean: $(TARGET)
	rm -f $(TARGET) $(OBJ)
docs:
	doxygen docs/Doxyfile
	@echo "Docs generated at docs/html/index.html"
tidy:
	clang-tidy $(SRC) -- $(CFLAGS) -Iinclude
