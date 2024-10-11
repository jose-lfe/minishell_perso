#include "minishell.h"

char	*copy_command(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	i = 0;
	j = 0;
	len = command_length(input);
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (j < len)
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
