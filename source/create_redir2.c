#include "minishell.h"

char	*copy_redir(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	i = 0;
	j = 0;
	len = filename_length(input);
	copy = malloc((len + 1) * sizeof(char));
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
	new->index = 0;
	new->filename = NULL;
	new->heredoc = false;
	new->next = NULL;
}

void	initialize_outpath(t_outpath *new)
{
	new->index = 0;
	new->filename = NULL;
	new->append = false;
	new->next = NULL;
}
