/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/25 13:18:23 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
commencer par verifier qu'il s'agit pas d'une des 7 commandes faite
s'occuper des pipes et redirection 
fork // regarder pipex 
execve
*/

void	start_exec(t_command **command, t_envp **envp)
{
	t_command	*tmp;
	int			fd[2];
	pid_t		pid;

	tmp = *command;
	while (tmp)
	{
		if (tmp->pipein == true || tmp->pipeout == true)
		{
			tmp = tmp->next;
			continue ;
		}
	}
}

// signe << 
char	*ft_heredoc(t_data *data, char *lim, int fd, bool last)
{
    char    *input;
	char	*buffer;

	while (1)
	{
		input = readline("readline> ");
		if (ft_strnstr(input, lim, ft_strlen(input)) != 0)
			break;
		buffer = ft_strjoin_gnl(buffer, input);
	}
	if (last == true)
		ft_putstr_fd(buffer, fd);
	free(input);
	return (buffer);
}
