/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:19 by joseluis          #+#    #+#             */
/*   Updated: 2024/10/11 16:19:37 by jose-lfe         ###   ########.fr       */
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
	struct s_inpath		*inpath;
	struct s_outpath	*outpath;
	bool				pipein;
	bool				pipeout;
	bool				heredoc;
	struct s_command	*next;
}	t_command;

typedef struct s_temp_command
{
	char					*str;
	struct s_temp_command	*next;
}	t_temp_command;

typedef struct s_inpath
{
	int					index;
	char				*filename;
	bool				heredoc;
	struct s_inpath		*next;
}	t_inpath;

typedef struct s_outpath
{
	int					index;
	char				*filename;
	bool				append;
	struct s_outpath	*next;
}	t_outpath;

typedef struct s_data
{
	int					exit_status;
	int					base_stdin;
	int					base_stdout;
	struct s_envp		*envp;
	struct s_command	*command;
}	t_data;

typedef struct s_envp
{
	char			*var;
	char			*value;
	struct s_envp	*pre;
	struct s_envp	*next;
}	t_envp;

typedef struct s_parsing
{
	struct s_temp_command	*t;
	struct s_inpath			*in;
	struct s_outpath		*o;
	int						l;
	int						i;
	int						j;
}	t_parsing;

// main.c
char	*ft_change_str(char *old, char *convert, int start, int size);
int		dollar_converter(char **str, int i, t_envp **envp);
void	exit_statut(char **str, int i, t_data *data);
t_data	*init_data(void);
void	dollar_checker(char **str, t_envp **envp, t_data *data);

//envp.c
t_envp	*ft_copy_envp(char **env);
t_envp	*ft_new_var(char *str);
void	ft_add_back(t_envp **envp, t_envp *new);
void	ft_env(t_envp **envp, t_data *data);
void	ft_free_envp(t_envp *envp);

//export_unset.c
void	ft_print_export(t_envp **envp);
void	ft_pre_export(t_envp **envp, char **args, t_data *data);
void	ft_export(t_envp **envp, char *arg);
void	ft_pre_unset(t_envp **envp, char **args, t_data *data);
void	ft_unset(t_envp **envp, char *arg);

//cd_pwd.c
void	ft_cd(char **arg, t_data *data, t_envp **envp);
void	ft_pwd(t_data *data);
void	ft_change_old_pwd(char *buffer, t_envp **envp);
void	ft_change_new_pwd(t_envp **envp);

//echo_exit.c
void	ft_echo(char **arg, t_data *data);
void	ft_exit(char **arg, t_data *data);
void	ft_free_all(t_data *data, int exit_value);

//utils.c
char	*ft_get_var(char *str);
char	*ft_get_value(char *str);
int		ft_remove_dollar(char **str, char *var, int start, int size_var);
char	**convert_envp(t_envp **env);
char	*ft_fill_envp(t_envp *current);

//utils2.c
char	**ft_free_tab(char **envp);
char	**ft_get_path(t_envp **envp);
int		free_path_cmd_return_int(char **path, char *cmd, int value);
int		ft_strlen_var(char *str);
void	ft_change_var(t_envp **envp, char *arg, int size_var);

//exec.c
void	start_exec(t_data *data, t_command **command, t_envp **envp);
int		ft_exec_command(t_command *command, t_envp **envp, t_data *data);
void	ft_abs_rel_path(t_command *command, t_envp **envp, t_data *data);
void	ft_base_command(t_command *command, t_envp **envp, t_data *data);
void	ft_exec_base_command(t_command *command, t_envp **envp);

//exec2.c
void	ft_builtins(int i, t_command *command, t_envp **envp, t_data *data);
void	ft_exec_builtins(int i, t_command *command, t_envp **env, t_data *data);
int		ft_command_not_found(t_command *command, t_envp **envp, t_data *data);

//filedescriptor.c
void	ft_original_std(t_data *data, t_command *command, int index);
void	ft_copy_original_std(t_data *data);
void	ft_redirect_fd(int i, int *fd);

//redir.c
int		ft_inredir(t_inpath *inpath, int i);
int		ft_outredir(t_outpath *outpath, int i);
int		ft_outredir2(t_outpath *outpath);
void	ft_heredoc(t_inpath *inpath, int i);
void	ft_change_stdin(t_inpath *inpath);

//check_input.c
bool	check_input(char **str, t_envp **envp, t_data *data);

//check_quote.c
bool	check_quote(char *str);

//check.c
int		ft_check_command(t_command *command, t_envp **envp);
int		ft_check_base_command(t_command *command, t_envp **envp);
int		ft_check_absolute_relative_path(t_command *command);
int		should_ignore_dollar(const char *str, int pos);

//create_command.c
int		count_quote_command(char *input);

//create_redir.c
int		redir(char *input, t_inpath **inpath, t_outpath **outpath, int index);
int		create_inpath(char *input, t_inpath **inpath, int index);
int		create_outpath(char *input, t_outpath **outpath, int index);
int		skip_filename_length(char *input);
int		filename_length(char *input);
char	*copy_redir(char *input);

//convert_command.c
void	convert_command(t_parsing *p, t_command **command, char input);
char	*realloc_without_quote(char *str);
char	*realloc_without_d_quote(char **str);
char	*realloc_without_s_quote(char **str);
int		command_count(t_temp_command **command);
void	create_cmd_def(char **tb, t_command **command, t_parsing *p, char i);
void	free_temp_command(t_temp_command **command);
char	**create_tab(int size);
void	give_index_redir(t_inpath **inpath, t_outpath **outpath, int index);
int		command_length(char *input);
int		skip_command_length(char *str);
char	*copy_command(char *input);
bool	is_redir(char c);
bool	is_white_space(char c);
void	parsing(char *str, t_command **command);
void	parsing2(char *input, t_parsing *p);
void	init_struct_parsing(t_parsing **p);
int		create_command(char *input, t_temp_command **command);

//void	print_commands(t_command **head);
void	initialize_command(t_command *new);
void	set_pipein(t_command **head);
void	set_pipeout(t_command **head);

//free.c
void	free_command(t_command *command);
void	free_arg(char **arg);
void	free_inpath(t_inpath *inpath);
void	free_outpath(t_outpath *outpath);
void	ft_free_data(t_data *data);

void	print_command(t_command **head);
void	initialize_temp_command(t_temp_command *new);
void	initialize_inpath(t_inpath *new);
void	initialize_outpath(t_outpath *new);
void	setup_signals(void);

//setup.c
void	setup(int ac, char **av, char **env, t_envp **envp);

#endif