# Définition des cibles particulières
.PHONY: clean mrproper help


# Définition de variables :
	# Compilateur
CC =			gcc
	# Dossier contenant les sources
SRC_DIR = 		src
	# Dossier où créer les fichiers objets
OBJ_DIR = 		obj
	# Dossier où créer l'exécutable
BIN_DIR = 		bin
	# Nom de l'exécutable
EXEC = 			Labyrinthe
	# Noms des fichiers sources
SRCS = 			graph.c \
				link.c \
				node.c \
				dynamic_array.c \
				priorityQueue.c \
				main.c
	# Noms des fichiers objets (génération dynamique)
OBJS =		$(SRCS:%.c=$(OBJ_DIR)/%.o)


all : $(OBJS)
	$(CC) $(OBJS) -o $(BIN_DIR)/$(EXEC)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $< -o $@
	
check :
	if [ ! -e bin ]; then mkdir bin; fi
	if [ ! -e obj ]; then mkdir obj; fi

clean :
	rm -fv $(OBJ_DIR)/*.o

mrproper :
	rm -fv $(OBJ_DIR)/*.o
	rm -fv $(BIN_DIR)/$(EXEC)

