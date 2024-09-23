/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:19 by joseluis          #+#    #+#             */
/*   Updated: 2024/04/25 15:34:29 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_info
{
	char	**path;
	char	**av;
	char	**env;
	int		infile_error;
}	t_info;

int		ft_error(char *command, char **cmd, int i);
void	ft_error_pipe(char **path);
void	ft_error_fork(char **path);
void	ft_free_path(char **path);
void	ft_free_process(char **path, char **command);
int		ft_read_buffer(char *buffer, ssize_t b_read);
void	ft_child_process(t_info *info, int i, int *fd);
void	ft_parent_process(t_info *info, int j);
void	ft_start(int ac, char *av[], char *env[]);
t_info	*ft_check_error(int ac, char *av[], char *env[]);
void	ft_check_command(int i, int ac, char **path, char **av);
char	**get_path(char *env[]);
void	ft_heredoc(int ac, char **av, char **env);

#endif