/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:13:48 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/17 14:46:28 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*realloc_without_quote(char *str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			new = realloc_without_d_quote(str);
			return (new);
		}
		else if (str[i] == '\'')
		{
			new = realloc_without_s_quote(str);
			return (new);
		}
		i++;
	}
	return (str);
}

char	*realloc_without_d_quote(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
		i++;
	len = i - 2;
	new = malloc((len + 1) * sizeof(char));
	i = 0;
	while (j < len)
	{
		if (str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*realloc_without_s_quote(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
		i++;
	len = i - 2;
	new = malloc((len + 1) * sizeof(char));
	i = 0;
	while (j < len)
	{
		if (str[i] != '\'')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}
