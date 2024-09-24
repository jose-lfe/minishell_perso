/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:49:26 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/24 13:53:37 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a modifier car erreur si  "  '  "  '
int	check_open_quote(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 1;
	dq = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			sq = sq * -1;
		if (str[i] == '"')
			dq = dq * -1;
		i++;
	}
	if (sq == 1 && dq == 1)
		return (0);
	ft_printf("Error: open quote \n");
	return (1);
}

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

int	dollar_converter(char **str, int i, char **env)
{
	int		size_var;
	char	*var;
	char	*convert;
	int		start;

	start = i;
	i++;
	while ((*str)[i] && ft_isalpha((*str)[i]))
		i++;
	size_var = i - start - 1;
	var = ft_substr(*str + 1, start, size_var);
	i = 0;
	while (env[i] && ft_strncmp(env[i], var, size_var) != 0)
		i++;
	if (!env[i])
	{
		free(var);
		return (1);
	}
	convert = ft_strdup(env[i] + size_var + 1);
	*str = ft_change_str(*str, convert, start, size_var);
	free(convert);
	free(var);
	return (0);
}

void	exit_statut(char *str, int i)
{
	i++;
	ft_printf("exit statut to change in : %s\n", str);
}

void	dollar_checker(char **str, char **env)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (ft_isalpha((*str)[i + 1]))
			{
				if (dollar_converter(str, i, env) == 0)
				{
					i = 0;
					continue ;
				}
			}
			if ((*str)[i + 1] == '?')
			{
				exit_statut(*str, i);
			}
		}
		i++;
	}
}

// t_data *data	init_data(char **av, char *env)

int	main(int ac, char **av, char **env)
{
	t_envp		*envp;
	char		*input;
	t_command	*command;

	(void)av;
	(void)ac;
	command = NULL;
	ft_copy_envp(env, &envp);
	ft_env(&envp);
	ft_unset(&envp, "PATH");
	ft_env(&envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (check_open_quote(input) != 0)
			return (1);
		dollar_checker(&input, env);
		ft_printf("%s\n", input);
		parsing_input(input, &command);
		//execution();
		//free_cmd_input();
	}
	ft_free_envp(envp);
	return (0);
}
/*
int	main(int ac, char **av, char **env)
{
	t_envp		*envp;
	char		*input;
	t_command	*command;

	(void)av;
	(void)ac;
	command = NULL;
	create_env();
	while (1)
	{
		input = readline("minishell> ");
		checking_input();
		parsing_input(input, &command);
		execution();
		free_cmd_input();
	}
	ft_free_envp(envp);
	return (0);
}
pid_t	current_process;
current_process = NULL;

int	main(int ac, char **av, char **env)
{
	t_envp		*envp;
	char		*input;
	t_command	*command;

	(void)av;
	(void)ac;
	command = NULL;
	setup_signals();
	create_data();
	while (1)
	{
		input = readline("minishell> ");
		checking_input();
		parsing_input(input, &command);
		execution();
		free_cmd_input();
	}
	ft_free_envp(envp);
	return (0);
}

free les commandes et linput apres lexecution
gerer les signaux
echo
exit
*/