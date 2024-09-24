#include "minishell.h"

bool	is_separator(char c)
{
	if (c == '|')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	is_white_space(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\t')
		return (true);
	if (c == '\n')
		return (true);
	if (c == '\r')
		return (true);
	if (c == '\v')
		return (true);
	if (c == '\f')
		return (true);
	return (false);
}
