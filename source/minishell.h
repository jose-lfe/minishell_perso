/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:19 by joseluis          #+#    #+#             */
/*   Updated: 2024/10/02 11:14:04 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <term.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_command
{
	char				**arg;
	bool				in_redir;
	struct s_inpath		*in_path;
	bool				out_redir;
	struct s_outpath	*out_path;
	bool				pipein;
	bool				pipeout;
	bool				heredoc;
	struct s_command	*next;
}	t_command;

typedef struct s_inpath
{
	char				*filename;
	bool				here_doc;
	struct s_inpath		*next;
}	t_inpath;

typedef struct s_outpath
{
	char				*filename;
	bool				append;
	struct s_outpath	*next;
}	t_outpath;

typedef struct s_data
{
	int					exit_status;
	int					base_stdin;
	int					base_stdout;
	struct s_envp		**envp;
	struct s_command	**command;
}	t_data;

typedef struct s_envp
{
	char			*var;
	char			*value;
	struct s_envp	*pre;
	struct s_envp	*next;
}	t_envp;

// main.c
int		check_open_quote(char *str);
char	*ft_change_str(char *old, char *convert, int start, int size);
int		dollar_converter(char **str, int i, t_envp **envp);
void	exit_statut(char *str, int i);
void	dollar_checker(char **str, t_envp **envp);

//envp.c
void	ft_copy_envp(char **env, t_envp **envp);
t_envp	*ft_new_var(char *str);
void	ft_add_back(t_envp **envp, t_envp *new);
void	ft_env(t_envp **envp);
void	ft_free_envp(t_envp *envp);

//export_unset.c
void	ft_print_export(t_envp **envp);
void	ft_pre_export(t_envp **envp, char **args);
void	ft_export(t_envp **envp, char *arg);
void	ft_pre_unset(t_envp **envp, char **args);
void	ft_unset(t_envp **envp, char *arg);

//cd_pwd.c
void	ft_cd(char **arg, t_data *data);
void	ft_pwd(char **arg, t_data *data);

//utils.c
char	*ft_get_var(char *str);
char	*ft_get_value(char *str);
int		ft_free_str_and_return_1(char *str);
char	**convert_envp(t_envp **env);
char	*ft_fill_envp(t_envp *current);

//utils2.c
char	*ft_free_tab(char **envp);
char	**ft_get_path(t_envp **envp);
int		free_path_cmd_return_int(char **path, char *cmd, int value);
int		ft_strlen_var(char *str);
void	ft_change_var(t_envp **envp, char *arg, int size_var);

//exec.c
void	start_exec(t_data *data, t_command **command, t_envp **envp);
int		ft_exec_command(t_command *command, t_envp **envp);
void	ft_absolute_relative_path(t_command *command, t_envp **envp);
void	ft_base_command(t_command *command, t_envp **envp);
void	ft_exec_base_command(t_command *command, t_envp **envp);

//exec2.c
void	ft_builtins(int i, t_command *command, t_envp **envp);
void	ft_exec_builtins(int i, t_command *command, t_envp **envp);
int		ft_command_not_found(t_command *command, t_envp **envp);

//filedescriptor.c
void	ft_original_std(t_data *data, t_command *command);
void	ft_copy_original_std(t_data *data);
void	ft_redirect_fd(int i, int *fd);

//redir.c
int		ft_inredir(t_inpath *inpath);
int		ft_outredir(t_outpath *outpath);
void	ft_heredoc(t_inpath *inpath);
void	ft_change_stdin(t_inpath *inpath);

//check.c
int		ft_check_command(t_command *command, t_envp **envp);
int		check_base_command(t_command *command, t_envp **envp);
int		ft_check_absolute_relative_path(t_command *command);

int		command_length(char *str);
int		arg_length(char *str, int c);
int		count_arg(char *str);
bool	is_separator(char c);
bool	is_pipe(char c);
bool	is_white_space(char c);
void	parsing_input(char *str, t_command **command);
void	create_command(char *str, t_command **command);
void	print_commands(t_command **head);
void	initialize_command(t_command *new);
void	fill_command(char *str, t_command *command);
char	**create_tab_for_command(char *str);
char	*create_string(char *str, int c);
void	append_to_list(t_command **command, t_command *new);
void	check_for_redir(char *str, t_command *command);
void	file_redir(char *str, t_command *command, int flag);
void	set_pipeout(t_command **head);

void	setup_signals(void);

#endif