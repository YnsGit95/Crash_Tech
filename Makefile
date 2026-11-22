CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -O2 -Iinclude
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:src/%.c=obj/%.o)
EXEC    = crashTech
FILE   ?= data/data.csv

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@

obj/%.o: src/%.c include/*.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

run: $(EXEC)
	./$(EXEC)

year: $(EXEC)
	./$(EXEC) YEAR_DATA $(FILE)

age: $(EXEC)
	./$(EXEC) AGE_DATA $(FILE)

crash: $(EXEC)
	./$(EXEC) CRASH_DATA $(FILE)

clean:
	rm -rf obj $(EXEC)

.PHONY: all run year age crash clean
