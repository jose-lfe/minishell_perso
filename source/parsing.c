/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:14:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/22 14:06:27 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_command **command, t_data *data)
{
	t_parsing	*p;

	init_struct_parsing(&p);
	while (input[p->i] != '\0')
	{
		parsing2(input, p);
		convert_command(p, command, input[p->i]);
		if (input[p->i] == '|')
		{
			p->i++;
			p->j++;
			set_pipein(command);
		}
	}
	set_pipeout(command);
	p->j = 0;
	free(p);
	data->command = *command;
}
	//print_command(command);

void	init_struct_parsing(t_parsing **p)
{
	*p = malloc(sizeof(t_parsing));
	(*p)->t = NULL;
	(*p)->in = NULL;
	(*p)->o = NULL;
	(*p)->i = 0;
	(*p)->j = 0;
}

void	parsing2(char *input, t_parsing *p)
{
	while (input[p->i] != '|' && input[p->i] != '\0')
	{
		p->l = 0;
		while (is_white_space(input[p->i]))
			p->i++;
		if (input[p->i] == '\0' || input[p->i] == '|')
			break ;
		else if (is_redir(input[p->i]))
			p->l = redir(input + p->i, &(p->in), &(p->o), p->j);
		else
			p->l = create_command(input + p->i, &(p->t));
		p->i = p->i + p->l;
		if (p->l == 0)
			p->i++;
	}
}

/*
void	print_command(t_command **head)
{
    t_command	*current = *head;

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
	t_command	*current;

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
	t_command	*current;

	current = *head;
	if (current == NULL)
		return ;
	while (current->next != NULL)
	{
		if (current->pipein == true)
			current->next->pipeout = true;
		current = current->next;
	}
	return ;
}
