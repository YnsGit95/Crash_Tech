# Compilateur et options
CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude
LDFLAGS =

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Exécutable
EXEC = crashTech

# Modules compilés (on ajoute age_data, avl et crash_data quand ils seront prêts)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/csv.c \
       $(SRC_DIR)/year_data.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Tous les en-têtes : si un .h change, tout est recompilé
HEADERS = $(wildcard $(INC_DIR)/*.h)

all: $(EXEC)

# Édition de liens
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation de chaque .c en .o (obj/ est créé si besoin)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(EXEC)
	./$(EXEC)

# Nettoyage : supprime obj/ et l'exécutable
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

rebuild: clean all

.PHONY: all run clean rebuild