NAME = minishell
CC = gcc
LDFLAGS = -lreadline
CFLAGS = -Wall -Wextra -Werror 
LIBFT_PATH = ./library/libft
LIBFT = -L$(LIBFT_PATH) -lft
LIBFT_SENTINEL = $(LIBFT_PATH)/libft_built.sentinel
OBJ_PATH = ./obj
AR = ar

SRCS = 	source/main.c \
		source/cd_pwd.c \
		source/check_input.c \
		source/check_pipe.c \
		source/check_quote.c \
		source/check.c \
		source/convert_command.c \
		source/convert_command2.c \
		source/create_command.c \
		source/create_command2.c \
		source/create_redir.c \
		source/create_redir2.c \
		source/echo_exit.c \
		source/envp.c \
		source/export_unset.c \
		source/exec.c \
		source/exec2.c \
		source/free.c \
		source/heredoc.c \
		source/filedescriptor.c \
		source/parsing_utils.c \
		source/parsing.c \
		source/redir.c \
		source/setup.c \
		source/signal.c \
		source/utils.c \
		source/utils2.c \
		source/new_exec.c \
		source/new_exec2.c \

OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_PATH)/,$(notdir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_SENTINEL)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -o $(NAME) $(LDFLAGS)

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