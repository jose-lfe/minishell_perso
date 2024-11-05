/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:49:26 by joseluis          #+#    #+#             */
/*   Updated: 2024/11/05 12:25:43 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_glob_pid = 0;

char	*ft_change_str(char *old, char *convert, int start, int size)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(old) - size + ft_strlen(convert) + 1)
			* sizeof(char));
	if (!new)
		return (NULL);
	while (old[i] && i < start)
	{
		new[i] = old[i];
		i++;
	}
	while (convert[j])
		new[i++] = convert[j++];
	while (old[i - ft_strlen(convert) + size + 1])
	{
		new[i] = old[i - ft_strlen(convert) + size + 1];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

int	dollar_converter(char **str, int i, t_envp **envp)
{
	int		size_var;
	char	*var;
	char	*convert;
	int		start;
	t_envp	*tmp;

	if (should_ignore_dollar(*str, i) == 1)
		return (1);
	start = i;
	i++;
	while ((*str)[i] && ft_isalpha((*str)[i]))
		i++;
	size_var = i - start - 1;
	var = ft_substr(*str + 1, start, size_var);
	i = 0;
	tmp = *envp;
	while (tmp && ft_compare(var, tmp->var) == 0)
		tmp = tmp->next;
	if (!tmp)
		return (ft_remove_dollar(str, var, start, size_var));
	convert = ft_strdup(tmp->value);
	*str = ft_change_str(*str, convert, start, size_var);
	free(convert);
	free(var);
	return (0);
}

void	dollar_checker(char **str, t_envp **envp, t_data *data)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (ft_isalpha((*str)[i + 1]))
			{
				if (dollar_converter(str, i, envp) == 0)
				{
					i = 0;
					continue ;
				}
			}
			if ((*str)[i + 1] == '?')
			{
				exit_statut(str, i, data);
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

t_data	*init_data(t_envp *envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(0);
	ft_copy_original_std(data);
	data->exit_status = 0;
	data->flag = 0;
	data->envp = envp;
	data->command = NULL;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_envp		*envp;
	char		*input;
	t_data		*data;

	setup(ac, av, env, &envp);
	data = init_data(envp);
	while (1)
	{
		data->command = NULL;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (check_input(&input, data))
			continue ;
		dollar_checker(&input, &envp, data);
		parsing(input, &(data->command), data);
		start(data, &(data->command), &envp);
		free(input);
	}
	ft_free_all(data, 0);
	rl_clear_history();
	return (0);
}
