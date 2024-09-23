/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:48:08 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/07 13:09:30 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdlib.h>
#include <stdio.h>
*/
static int	words(char const *s, char c);
static char	*fill(char const *s, char c, int *i);
static void	ft_free(char **res, int j);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;
	int		mots;

	mots = words(s, c);
	res = malloc((mots + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (j < mots)
	{
		res[j] = fill(s, c, &i);
		if (!res[j])
		{
			ft_free(res, j);
			return (NULL);
		}
		j++;
	}
	res[j] = NULL;
	return (res);
}

static int	words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (words);
}

static char	*fill(char const *s, char c, int *i)
{
	char	*res;
	int		start;
	int		j;
	int		ii;

	j = 0;
	ii = *i;
	while (s[ii] == c)
		ii++;
	start = ii;
	while (s[ii] != c && s[ii] != '\0')
	{
		ii++;
		j++;
	}
	res = malloc((j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (start < ii)
		res[j++] = s[start++];
	res[j] = '\0';
	*i = ii;
	return (res);
}

static void	ft_free(char **res, int j)
{
	while (j >= 0)
	{
		free(res[j]);
		j--;
	}
	free(res);
}
/*
int main(void)
{
	char c = 'h';
	char *str = "lahvoiturehmange";

	char **res = ft_split(str, c);
	printf("%s\n", res[0]);
	printf("%s\n", res[1]);
	printf("%s\n", res[2]);
	return 0;
}
*/