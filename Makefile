CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
SRC     = src/main.c src/menu.c src/utils.c
OBJ     = $(SRC:src/%.c=obj/%.o)
EXEC    = crashTech

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@

obj/%.o: src/%.c include/*.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf obj $(EXEC)

.PHONY: all run clean