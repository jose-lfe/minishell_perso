NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./library/libft
LIBFT = -L$(LIBFT_PATH) -lft
LIBFT_SENTINEL = $(LIBFT_PATH)/libft_built.sentinel
BONUS_SENTINEL = ./obj/bonus_built.sentinel
OBJ_PATH = ./obj

SRCS = src/main.c src/error.c src/utils.c
BONUS_SRCS = src_b/main_bonus.c src_b/error_bonus.c src_b/utils_bonus.c src_b/bonus_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_PATH)/,$(notdir $(OBJS)))
BONUS_OBJS := $(addprefix $(OBJ_PATH)/,$(notdir $(BONUS_OBJS)))

# Cible principale
all: $(NAME)

# Cible pour le programme principal
$(NAME): $(OBJS) | $(LIBFT_SENTINEL)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -o $(NAME)

# Cible pour les bonus avec gestion de sentinel
bonus: $(BONUS_SENTINEL)
$(BONUS_SENTINEL): $(BONUS_OBJS) | $(LIBFT_SENTINEL)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -lm -o $(NAME)
	touch $(BONUS_SENTINEL)

# Règles de compilation des fichiers source
$(OBJ_PATH)/%.o: src/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

$(OBJ_PATH)/%.o: src_b/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

# Création du répertoire objet si nécessaire
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# Construction de la libft et création d'un sentinel
$(LIBFT_SENTINEL):
	make -C $(LIBFT_PATH) bonus
	touch $(LIBFT_SENTINEL)

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

# Nettoyage complet, y compris le programme compilé
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_SENTINEL) $(BONUS_SENTINEL)
	make -C $(LIBFT_PATH) fclean

# Recompilation complète
re: fclean all

# Déclaration des cibles ne produisant pas de fichier
.PHONY: all clean fclean re bonus
