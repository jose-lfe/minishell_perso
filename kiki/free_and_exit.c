//ici on va free tous les mallocs et on va exit le programme
//les choses a free sont les tokens et les strings a l'interieur des tokens

#include "minishell.h"

void	free_token(t_token **tok, int code)
{
	t_token	*current;

	current = *tok;
	while (current)
	{
		if (current->str)
			free(current->str)
		free(current)
		current = current->next;
	}
	return ;
}