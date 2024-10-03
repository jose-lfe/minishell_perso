#include "minishell.h"

int	create_redir(char *input, t_inpath **inpath, t_outpath **outpath)
{
	int	i;

	i = 0;
	if (*input == '<')
		i = create_inpath(input, inpath);
	else if (*input == '>')
		i = create_outpath(input, outpath);
	return (i);
}


int	create_inpath(char *input, t_inpath **inpath)
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


int	create_outpath(char *input, t_outpath **outpath)
{
	int		i;
	char		*filename;
	t_outpath	*new;
	t_outpath	*current;

	i = skip_filename_length(input);
	new = malloc(sizeof(t_outpath));
	initialize_outpath(new);
	filename = copy_redir(input);
	new->filename = filename;	
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


char *copy_redir(char *input)
{
	int		i;
	int		j;
	int		len;
	char 	*copy;

	i = 0;
	j = 0;
	len = filename_length(input);
	copy = malloc((len + 1 )* sizeof(char));
	if (!copy)
		return (NULL);
	while (is_redir(input[i]) && input[i] != '\0')
		i++;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0')
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
void	initialize_inpath(t_inpath *new)
{
	new->filename = NULL;
	new->heredoc = false;
	new->next = NULL;
}
void	initialize_outpath(t_outpath *new)
{
	new->filename = NULL;
	new->append = false;
	new->next = NULL;
}
