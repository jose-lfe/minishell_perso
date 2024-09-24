NAME = minishell
CC = gcc
LDFLAGS = -lreadline
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./library/libft
LIBFT = -L$(LIBFT_PATH) -lft
LIBFT_SENTINEL = $(LIBFT_PATH)/libft_built.sentinel
OBJ_PATH = ./obj

SRCS = 	source/main.c \
		source/envp.c \
		source/export_unset.c \
		source/commands_utils.c \
		source/transform_input_counters.c \
		source/transform_input.c \
		source/signal.c \
		source/utils.c
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_PATH)/,$(notdir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_SENTINEL)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -lm -o $(NAME)

$(OBJ_PATH)/%.o: source/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIBFT_SENTINEL):
	make -C $(LIBFT_PATH) bonus
	touch $(LIBFT_SENTINEL)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_SENTINEL)
	make -C $(LIBFT_PATH) fclean

re: fclean all