/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:59 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/23 12:13:39 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_export(t_envp **envp)
// {
// 	t_envp	*tmp;
	
// }

void	ft_unset(t_envp **envp, char *arg)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, arg, ft_strlen(arg)) == 0)
		{
			if (tmp->pre == NULL)
				*envp = tmp->next;
			else
				tmp->pre->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->pre = tmp->pre;
			free(tmp->var);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
