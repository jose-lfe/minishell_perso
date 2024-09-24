/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/24 11:36:25 by jose-lfe         ###   ########.fr       */
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
		if (ft_must_be_parent(tmp, envp) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
	}
}

int	ft_must_be_parent(t_command *command, t_envp **envp)
{
	if (ft_strncmp(command->arg[0], "cd", 2))

}

// signe << 
char	*ft_heredoc(t_data *data)
{
    char    *input;
	char	*buffer;

	while (1)
	{
		input = readline("readline> ");
		if (ft_strnstr(input, data->lim, ft_strlen(input)) != 0)
			break;
		buffer = ft_strjoin_gnl(buffer, input);
	}
	free(input);
	return (buffer);
	//ft_putstr_fd(buffer, STDIN_FILENO); si on veut plutot utiliser l'entré standar
}
