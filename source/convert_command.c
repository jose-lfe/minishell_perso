#include "minishell.h"

void	convert_command(t_parsing *p, t_command **command, char input)
{
	t_temp_command	*current;
	int				size;
	char			**tb;
	int				i;

	current = p->t;
	size = command_count(&(p->t));
	tb = create_tab(size);
	i = 0;
	while (i < size)
	{
		tb[i] = realloc_without_quote(current->str);
		current->str = NULL;
		current = current->next;
		i++;
	}
	create_command_def(tb, command, p, input);
	free_temp_command(&(p->t));
	p->t = NULL;
	return ;
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

void	create_command_def(char **tb, t_command **command, t_parsing *p, char i)
{
	t_command	*new;
	t_command	*current;

	new = malloc(sizeof(t_command));
	initialize_command(new);
	if (i == '|')
		new->pipeout = true;
	new->inpath = p->in;
	new->outpath = p->o;
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
	t_temp_command	*current;
	t_temp_command	*next;

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

	tb = malloc((size + 1) * sizeof(char *));
	if (!tb)
		return (NULL);
	tb[size] = NULL;
	return (tb);
}
