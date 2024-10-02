#include "minishell.h"

void	convert_command(t_temp_command **temp, t_command **command, t_inpath **inpath, t_outpath **outpath, char input)
{
	t_temp_command	*current;
	int				size;
	char			**tb;
	int				i;
	
	//remove_quote(temp);
	current = *temp;
	size = command_count(temp);
	tb = create_tab(size);
	i = 0;
	while (i < size)
	{
		tb[i] = current->str;
		current->str = NULL;
		current = current->next;
		i++;
	}
	create_command_def(tb, command, inpath, outpath, input);
	free_temp_command(temp);
	return ;
}
/*void	remove_quote(t_temp_command **temp)
{
	t_temp_command *current;
	int				start;
	int				end;

	current = *temp;
	start = 0;
	while (current)
	{
		end = ft_strlen(current->str) - 1;
		if (current->str[start] == '"' && current->str[end] == '"')
			current->str = realloc_without_quotes(current->str);
		else if (current->str[start] == '\'' && current->str[end] == '\'')
			current->str = realloc_without_quotes(current->str);
		current = current->next;
	}
	return ;
}*/

char	*realloc_without_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 1;
	j = 0;
	len = ft_strlen(str) - 2;
	new = malloc((len + 1)*sizeof(char));
	while (j < len)
	{
		new[j] = str[i];
		j++;
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
