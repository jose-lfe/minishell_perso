NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS =  -lreadline
SRC = main.c commands_utils.c transform_input_counters.c transform_input.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

all: $(NAME)