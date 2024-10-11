#include "minishell.h"

bool	check_quote_simple(char *sec_prev, char *prev, int *c_single)
{
	if (*prev == '"' && *sec_prev == '\'')
		return (true);
	*sec_prev = *prev;
	*prev = '\'';
	(*c_single)++;
	return (false);
}

bool	check_quote_double(char *sec_prev, char *prev, int *c_double)
{
	if (*prev == '\'' && *sec_prev == '"')
		return (true);
	*sec_prev = *prev;
	*prev = '"';
	(*c_double)++;
	return (false);
}

bool	check_quote(char *str)
{
	int		c_single;
	int		c_double;
	char	prev;
	char	sec_prev;
	int		i;

	c_single = 0;
	c_double = 0;
	prev = '\0';
	sec_prev = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			if (check_quote_simple(&sec_prev, &prev, &c_single))
				return (true);
		if (str[i] == '"')
			if (check_quote_double(&sec_prev, &prev, &c_double))
				return (true);
		i++;
	}
	if (c_single % 2 != 0 || c_double % 2 != 0)
		return (true);
	return (false);
}
