#include "minishell.h"

int	create_redir(char *input, t_inpath **inpath, t_outpath **outpath, int index)
{
	int	i;

	i = 0;
	if (*input == '<')
		i = create_inpath(input, inpath, index);
	else if (*input == '>')
		i = create_outpath(input, outpath, index);
	return (i);
}

int	create_inpath(char *input, t_inpath **inpath, int index)
{
	int			i;
	char		*filename;
	t_inpath	*new;
	t_inpath	*current;

	i = skip_filename_length(input);
	new = malloc(sizeof(t_inpath));
	initialize_inpath(new);
	filename = copy_redir(input);
	new->filename = filename;
	new->index = index;
	if (*input == '<' && *(input + 1) == '<')
		new->heredoc = true;
	else
		new->heredoc = false;
	if (*inpath == NULL)
		*inpath = new;
	else
	{
		current = *inpath;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}

int	create_outpath(char *input, t_outpath **outpath, int index)
{
	int			i;
	char		*filename;
	t_outpath	*new;
	t_outpath	*current;

	i = skip_filename_length(input);
	new = malloc(sizeof(t_outpath));
	initialize_outpath(new);
	filename = copy_redir(input);
	new->filename = filename;
	new->index = index;
	if (*input == '>' && *(input + 1) == '>')
		new->append = true;
	else
		new->append = false;
	if (*outpath == NULL)
		*outpath = new;
	else
	{
		current = *outpath;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}

int	skip_filename_length(char *input)
{
	int	i;

	i = 0;
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
		i++;
	return (i);
}

int	filename_length(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
	{
		i++;
		c++;
	}
	return (c);
}
