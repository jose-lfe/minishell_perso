#include "minishell.h"

void	convert_command(t_temp_command **temp, t_command **command, t_inpath **inpath, t_outpath **outpath, char input)
{
	t_temp_command	*current;
	int				size;
	char			**tb;
	int				i;
	
	current = *temp;
	size = command_count(temp);
	tb = create_tab(size);
	i = 0;
	while (i < size)
	{
		tb[i] = realloc_without_quote(current->str);
		current->str = NULL;
		current = current->next;
		i++;
	}
	create_command_def(tb, command, inpath, outpath, input);
	free_temp_command(temp);
	*temp = NULL;
	return ;
}

char	*realloc_without_quote(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			len++;
		i++;
	}
	new = malloc((len + 1)*sizeof(char));
	i = 0;
	while (j < len)
	{
		if (str[i] != '"' && str[i] != '\'')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}



int	command_count(t_temp_command **command)
{
	t_temp_command	*current;
	int				i;
	
	current = *command;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	create_command_def(char **tb, t_command **command, t_inpath **inpath, t_outpath **outpath, char input)
{
	t_command	*new;
	t_command	*current;

	new = malloc(sizeof(t_command));
	initialize_command(new);
	if (input == '|')
		new->pipeout = true;
	new->inpath = *inpath;
	new->outpath = *outpath;
	new->arg = tb;
	if (*command == NULL)
		*command = new;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return ;
}

void	free_temp_command(t_temp_command **command)
{
	t_temp_command *current;
	t_temp_command *next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}


char	**create_tab(int size)
{
	char	**tb;

	tb = malloc((size + 1) * sizeof(char*));
	if (!tb)
		return (NULL);
	tb[size] = NULL;
	return (tb);
}
