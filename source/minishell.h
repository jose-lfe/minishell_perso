/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:19 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/23 12:13:30 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // write, access, open, read, close, fork, dup, dup2, pipe, getcwd, chdir, unlink, execve, isatty
# include <fcntl.h>      // open, O_ constants
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>     // opendir, readdir, closedir
# include <sys/stat.h>   // stat, lstat, fstat
# include <string.h>     // strerror
# include <termios.h>    // tcsetattr, tcgetattr, ioctl
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (ou <termcap.h> selon la version)
# include <readline/readline.h>   // readline, add_history
# include <readline/history.h>    // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <sys/ioctl.h>  // ioctl
# include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <stddef.h>
# include <stdbool.h>

typedef struct s_token
{
	char			*str;
	struct s_token 	*next;
}	t_token;

typedef struct s_data
{
	char	**env;
	char	*lim;
	int		exit_statue;
}	t_data;

typedef struct s_envp
{
	char	*var;
	struct s_envp	*pre;
	struct s_envp	*next;
}	t_envp;

int	check_open_quote(char *str);
char	*ft_change_str(char *old, char *convert, int start, int size);
int		dollar_converter(char **str, int i, char **env);
void	exit_statut(char *str, int i);
void	dollar_checker(char **str, char **env);

void	ft_copy_envp(char **env, t_envp **envp);
t_envp	*ft_new_var(char *str);
void	ft_add_back(t_envp **envp, t_envp *new);
void	ft_env(t_envp **envp);
void	ft_free_envp(t_envp *envp);

void	ft_unset(t_envp **envp, char *arg);

#endif