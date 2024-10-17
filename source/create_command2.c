/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:13:53 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/17 14:01:35 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_command(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	i = 0;
	j = 0;
	len = command_length(input);
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (j < len)
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
