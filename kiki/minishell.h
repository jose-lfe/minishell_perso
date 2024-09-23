#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command
{
	char				**arg;
	bool				in_redir;
	char				*in_path;
	bool				out_redir;
	char				*out_path;
	bool				append;
	bool				*pipein;
	bool				*pipeout;
	bool				*heredoc;
	struct s_command	*next;
}	t_command;


int	command_length(char *str);
int	arg_length(char *str, int c);
int	count_arg(char *str);
bool	is_separator(char c);
bool	is_white_space(char c);
void	parsing_input(char *str, t_command **command);
void	create_command(char *str, t_command **command);
void print_commands(t_command **head);
void	initialize_command(t_command *new);
void	fill_command(char *str, t_command *command);
char	**create_tab_for_command(char *str);
char	*create_string(char *str, int c);
void	append_to_list(t_command **command, t_command *new);
#endif