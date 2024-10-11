/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:14:32 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/11 16:14:33 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup(int ac, char **av, char **env, t_envp **envp)
{
	(void)ac;
	(void)av;
	*envp = ft_copy_envp(env);
	setup_signals();
}
