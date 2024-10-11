#include "minishell.h"

int	create_command(char *input, t_temp_command **command)
{
	int				i;
	char			*str;
	t_temp_command	*new;
	t_temp_command	*current;

	i = skip_command_length(input);
	printf("%d\n", i);
	new = malloc(sizeof(t_temp_command));
	initialize_temp_command(new);
	str = copy_command(input);
	new->str = str;
	if (*command == NULL)
		*command = new;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}

int	skip_command_length(char *input)
{
	int	i;

	i = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	if ((input[i] == '"') || (input[i] == '\''))
	{
		i = i + count_quote_command(input + i);
		return (i);
	}
	while (!is_white_space(input[i]) && input[i] != '\0'
		&& input[i] != '|' && !is_redir(input[i]))
		i++;
	return (i);
}

int	count_quote_command(char *input)
{
	int		i;
	char	q;
	int		last;

	i = 0;
	q = input[i];
	last = 0;
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == q)
			last = i;
		i++;
	}
	return (last + 1);
}

void	initialize_temp_command(t_temp_command *new)
{
	new->str = NULL;
	new->next = NULL;
}

int	command_length(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	if ((input[i] == '"') || (input[i] == '\''))
	{
		c = count_quote_command(input + i) + 1;
		return (c);
	}
	while (!is_white_space(input[i]) && input[i] != '\0'
		&& input[i] != '|' && !is_redir(input[i]))
	{
		i++;
		c++;
	}
	return (c);
}
