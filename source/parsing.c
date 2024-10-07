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
void	parsing(char *input, t_command **command)
{
	t_temp_command 	*temp_cmd;
	t_inpath		*inpath;
	t_outpath		*outpath;
	int				length;
	int				i;
	int				j;

	temp_cmd = NULL;
	inpath = NULL;
	outpath = NULL;
	i = 0;
	j = 0;

	//check_open_quotes(input);
	//check_errors;

	printf("debut\n"); //
	while (input[i] != '\0')
	{
		while (input[i] != '|' && input[i] != '\0')
		{
			length = 0;
			while (is_white_space(input[i]))
				i++;
			if (input[i] == '\0' || input[i] == '|')
				break ;
			else if (is_redir(input[i]))
				length = create_redir(input + i, &inpath, &outpath, j);
			else 
				length = create_command(input + i, &temp_cmd);
			i = i + length;
			if (length == 0)
				i++;
		}
		convert_command(&temp_cmd, command, &inpath, &outpath, input[i]);
		if (input[i] == '|')
		{
			i++;
			j++;
			set_pipein(command);
		}
	}
	set_pipeout(command);
	//print_command(command);
	j = 0;
}


int	create_command(char *input, t_temp_command **command)
{
	int			i;
	char		*str;
	t_temp_command	*new;
	t_temp_command	*current;

	i = skip_command_length(input);
	new = malloc(sizeof(t_temp_command));
	initialize_temp_command(new);
	str = copy_command(input);
	new->str = str;
	if (*command == NULL)
		*command = new;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (i);
}
int	skip_command_length(char *input)
{
	int	i;

	i = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0' && input[i] != '|')
		i++;
	return (i);
}
void	initialize_temp_command(t_temp_command *new)
{
	new->str = NULL;
	new->next = NULL;
}


int	command_length(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0' && input[i] != '|')
	{
		i++;
		c++;
	}
	return (c);
}
char *copy_command(char *input)
{
	int		i;
	int		j;
	int		len;
	char 	*copy;

	i = 0;
	j = 0;
	len = command_length(input);
	copy = malloc((len + 1 )* sizeof(char));
	if (!copy)
		return (NULL);
	while (is_white_space(input[i]) && input[i] != '\0')
		i++;
	while (!is_white_space(input[i]) && input[i] != '\0' && input[i] != '|')
	{
		copy[j] = input[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
/*void print_command(t_command **head)
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
        if (current->inpath)
        {
            printf("  Input redirection: in\n");
        }
        else
        {
            printf("  No input redirection\n");
        }

        // Imprimer la redirection de sortie
        if (current->outpath)
            printf("  Output redirection: out\n");
        else
        {
            printf("  No output redirection\n");
        }

        // Passer à l'élément suivant
        current = current->next;
        printf("\n");  // Ajouter une ligne vide entre les commandes
    }
}*/

void	set_pipein(t_command **head)
{
    t_command *current;

	current = *head;
	if (current == NULL)
		return ;
	while (current->next != NULL)
		current = current->next;
	current->pipein = true;
	return ;
}

void	set_pipeout(t_command **head)
{
    t_command *current = *head;
	while (current != NULL)
	{
		if (current->pipein == true)
			current->next->pipeout = true;
		current = current->next;
	}
	return ;
}

void	initialize_command(t_command *new)
{
	new->arg = NULL;
	new->inpath = NULL;
	new->outpath = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
}
//on est deja envoyer au bon endroit

// /!\ ATTENTION GERER LES EXIT ET FREE ENCORE
//SI JAMAIS les outfile et infile ne
//sarrete pas a lespace mais copie tout jusqa la fin ou la pipe