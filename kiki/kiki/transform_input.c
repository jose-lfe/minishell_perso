#include "minishell.h"

//ATTENTION il faut FREE chaque string et aussi chaque token donc double free car double malloc



//recevoir le string
//checker les quotes
//checker les quotes et si elles ne sont pas fermer demander un nouvel input utilisateurs
//utiliser strjoin pour coller les input ensemble
//checker les quotes
//par argument on entend chaque commande+args
//si cest pas vide on cree une premiere commande
//on copie jusquau separateur
//la liste cest genre commande into commande
//le plus simple cest que les commandes se pointe lune vers la suivante mais aussi que elles aient un element qui dit si
//y a un redirecteur et donc quel pointe vers le bon out ou in en fonction


//on malloc et on accroche lancien sur le nouveau
void	parsing_input(char *str, t_command **command)
{
	/*char *new_str;

	new_str = clean_string(str);
	check_quotes(new_str);
	check_errors();
	create_command(new_str, command);*/

	create_command(str, command);
}

void	create_command(char *str, t_command **command)
{
	t_command	*new;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		new = malloc(sizeof(t_command));
		/*if (!new)
			free_and_exit();*/
		initialize_command(new);
		fill_command(str + i, new);
		append_to_list(command, new);
		i = i + command_length(str + i); // attention a cette ligne si lindex est faux
	}
	print_commands(command);
	set_pipeout(command);
}

void print_commands(t_command **head)
{
    t_command *current = *head;

	printf("TEST:\n");
    while (current != NULL)
    {
        // Imprimer les arguments
        printf("Arguments:\n");
        if (current->arg != NULL)
        {
            for (int i = 0; current->arg[i] != NULL; i++)
            {
                printf("  arg[%d] = %s\n", i, current->arg[i]);
            }
        }
        else
        {
            printf("  No arguments\n");
        }

        // Imprimer la redirection d'entrée
        if (current->in_redir)
        {
            printf("  Input redirection: %s\n", current->in_path);
        }
        else
        {
            printf("  No input redirection\n");
        }

        // Imprimer la redirection de sortie
        if (current->out_redir)
        {
            printf("  Output redirection: %s\n", current->out_path);
            if (current->append)
            {
                printf("  Append mode\n");
            }
        }
        else
        {
            printf("  No output redirection\n");
        }

        // Passer à l'élément suivant
        current = current->next;
        printf("\n");  // Ajouter une ligne vide entre les commandes
    }
}

void	set_pipeout(t_command **head)
{
    t_command *current = *head;
	while (current != NULL)
	{
		if (current->pipein = true)
			current->next->pipeout = true;
		current = current->next;
	}
	return ;
}

void	initialize_command(t_command *new)
{
	new->arg = NULL;
	new->in_redir = false;
	new->in_path = NULL;
	new->out_redir = false;
	new->out_path = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->append = false;
	new->heredoc = false;
	new->next = NULL;
}

void	fill_command(char *str, t_command *command)
{
	command->arg = create_tab_for_command(str);
	check_for_redir(str, command);
}

char	**create_tab_for_command(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc((count_arg(str) + 1) * sizeof(char*));
	printf("%d ceci est le nb dargument", count_arg(str));
	/*if (!tab)
		free_and_exit(command);*/
	while (i < count_arg(str))
	{
		tab[i] = create_string(str, i);
		i++;
	}
	tab[i] = NULL;
	return(tab);
}
//on est deja envoyer au bon endroit
char	*create_string(char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = arg_length(str, c);
	printf("%d\n", arg_length(str, c));
	new = malloc((len + 1) * sizeof(char));
	/*if (!new)
		free_and_exit();*/
	while (c > 0)
	{
		while (!is_white_space(str[i]) && str[i] != '\0')
			i++;
		while ((is_white_space(str[i]) && str[i] != '\0'))
			i++;
		c--;
	}
	while (j < len)
	{
		new[j] = str[i + j];
		j++;
	}
	new[len] = '\0';
	return (new);
}

void	append_to_list(t_command **command, t_command *new)
{
	t_command	*current;

	current = *command;
	
	if (current == NULL)
		*command = new;
	if (current != NULL)
	{
		while (current->next)
			current = current->next;
	current->next = new;
	}
	return ;
}
void	check_for_redir(char *str, t_command *command)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !is_separator(str[i]))
		i++;
	if (str[i] == '\0')
		return ;
	else if (str[i] == '|')
		command->pipein = true;
	else if (str[i] == '<' && str[i + 1] == '<')
		command->heredoc = true;
	else if (str[i] == '>' && str[i + 1] == '>')
		command->append = true;
	else if (str[i] == '<')
		file_redir(str + i, command, -1);
	else if (str[i] == '>')
		file_redir(str + i, command, 1);
	return ;
}

void	file_redir(char *str, t_command *command, int flag)
{
	char	*path;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (is_white_space(str[i]))
		i++;
	path = malloc((arg_length(str + i, 0) + 1) * sizeof(char));
	while (str[i] != '|' && str[i] != '\0')
	{
		path[j] = str[i];
		i++;
		j++;
	}
	path[j] = '\0';
	if (flag == -1)
	{
		command->in_redir = true;
		command->in_path = path;
	}
	else if (flag == 1)
	{
		command->out_redir = true;
		command->out_path = path;
	}
}

// /!\ ATTENTION GERER LES EXIT ET FREE ENCORE
//SI JAMAIS les outfile et infile ne
//sarrete pas a lespace mais copie tout jusqa la fin ou la pipe