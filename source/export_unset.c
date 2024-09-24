/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:59 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/24 13:00:31 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		ft_printf("declare -x %s\n", tmp->var); // ajouter les quotes
		tmp = tmp->next;
	}
}

void	ft_pre_export(t_envp **envp, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		ft_print_export(envp);
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) == 0)
		{
			ft_printf("error: %s: not a valid identifier", args[i]);
			// manque changer la valeur de exit statut a 1
		}
		else
			ft_unset(envp, args[i]);
		i++;
	}
}

int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

void	ft_export(t_envp **envp, char *arg)
{
	t_envp	*tmp;
	int		size_var;

	tmp = *envp;
	size_var = ft_strlen_var(arg);
	while (tmp)
	{
		if (size_var == -1 && ft_strncmp(tmp->var, arg, ft_strlen(arg) == 0))
			return ;
		/*else if (ft_strncmp(tmp->var, arg, size_var) == 0)
			ft_change_var(envp, arg, size_var);*/
		tmp = tmp->next;
	}
	if (size_var == -1)
		ft_add_back(envp, ft_new_var(arg));
	else
	{
		// suite avec question avec kiki, si les quote sont supprimer ou pas 
	}
}

void	ft_pre_unset(t_envp **envp, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		ft_printf("unset: not enough arguments");
	while (args[i])
	{
		ft_unset(envp, args[i]);
		i++;
	}
	// il manque de mettre la valeur de exit status a 0
}

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
