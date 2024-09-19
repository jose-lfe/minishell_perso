/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:12:39 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/06 13:31:42 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find(char const *set, char c);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		deb;
	int		fin;
	char	*res;

	deb = 0;
	fin = ft_strlen(s1) - 1;
	while (find(set, s1[deb]) == 1)
		deb++;
	while (find(set, s1[fin]) == 1)
		fin--;
	if (fin < deb)
		return (ft_strdup(""));
	res = malloc((fin - (deb - 1) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (deb <= fin)
	{
		res[i] = s1[deb];
		i++;
		deb++;
	}
	res[i] = '\0';
	return (res);
}

static int	find(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
