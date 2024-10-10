/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:49:26 by joseluis          #+#    #+#             */
/*   Updated: 2024/10/10 17:30:41 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t glob_pid = 0;

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

	start = i;
	i++;
	while ((*str)[i] && ft_isalpha((*str)[i]))
		i++;
	size_var = i - start - 1;
	var = ft_substr(*str + 1, start, size_var);
	i = 0;
	tmp = *envp;
	while (tmp && ft_strncmp(tmp->var, var, ft_strlen(tmp->var)) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (ft_remove_dollar(str, var, start, size_var));
	convert = ft_strdup(tmp->value);
	*str = ft_change_str(*str, convert, start, size_var);
	free(convert);
	free(var);
	return (0);
}

void	exit_statut(char **str, int i, t_data *data)
{
	*str = ft_change_str(*str, ft_itoa(data->exit_status), i, 2);
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

t_data	*init_data(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(0);
	ft_copy_original_std(data);
	data->exit_status = 0;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_envp		*envp;
	char		*input;
	t_command	*command;
	t_data		*data;

	(void)av;
	(void)ac;
	command = NULL;
	envp = ft_copy_envp(env);
	data = init_data();
	setup_signals();
	while (1) 
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input)
			add_history(input);
		dollar_checker(&input, &envp, data);
		command = NULL;
		parsing(input, &command);
		start_exec(data, &command, &envp);
		free(input);
	}
	ft_free_data(data);
	ft_free_envp(envp);
	rl_clear_history();
	return (0);
}

/*
a faire demain : 
-ajouter index a heredoc << END cat -e > zzz | << end ls
-changer dollar_checker (verfier si dans quote, supprimer $text si n'existe pas)
-faire macro pour valeur de retour waitpid + autre endroit
-preparer les endroits ou tout free
-tout normer
-enjoy
*/