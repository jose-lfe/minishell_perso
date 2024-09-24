#include "minishell.h"

int	command_length(char *str)
{
	int	count;
	
	count = 0;
	while (!is_pipe(str[count]) && str[count] != '\0')
		count++;
	if (is_pipe(str[count]))
		count++;
	return (count);
}
int	arg_length(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (c > 0)
	{
		while (!is_white_space(str[i]) && str[i] != '\0')
			i++;
		while ((is_white_space(str[i]) && str[i] != '\0'))
			i++;
		c--;
	}
	while (!is_white_space(str[i]) && str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);

}

/*int	count_arg(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		while (!is_separator(str[i]) && str[i] != '\0')
			i++;
		count++;
	}
	return (count);
}/*/

int	count_arg(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0' && !is_separator(str[i]))
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] != '\0' && !is_separator(str[i]))
			count++;
		while (!is_white_space(str[i]) && !is_separator(str[i])
				&& str[i] != '\0')
			i++;
	}
		return (count);
}
//compte la longueur et renvoie la longueur de la commande
//par longueur de commande on entend la commande jusquau separateur
//attention a lhistoire des guillemets