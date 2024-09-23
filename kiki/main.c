#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	char		*input;

	(void)argc;
	(void)argv;
	(void)envp;
	command = NULL;
	while (1)
	{
	input = readline("minishell >");
	if (!input)
		break;
	if (*input)
		add_history(input);
	parsing_input(input, &command);
	/*while (commands[i] != NULL)
	{
		execve(commands[i][0], commands[i], envp);
		i++;
	}*/
	free(input);
	}
	return (0);
}