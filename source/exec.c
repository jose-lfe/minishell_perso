/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/23 15:38:54 by jose-lfe         ###   ########.fr       */
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
