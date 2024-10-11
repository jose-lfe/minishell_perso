/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:13:59 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/11 16:14:00 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_redir(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	i = 0;
	j = 0;
	len = filename_length(input);
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

void	initialize_inpath(t_inpath *new)
{
	new->index = 0;
	new->filename = NULL;
	new->heredoc = false;
	new->next = NULL;
}

void	initialize_outpath(t_outpath *new)
{
	new->index = 0;
	new->filename = NULL;
	new->append = false;
	new->next = NULL;
}
