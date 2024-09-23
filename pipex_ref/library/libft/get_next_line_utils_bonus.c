/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:53:02 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/01/30 13:45:56 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_true(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_substr_gnl(char *s, int start, int len)
{
	int				i;
	char			*res;

	if (s == NULL || ft_strlen_true(s) < start)
		return (NULL);
	if (len > ft_strlen_true(s + start))
		len = ft_strlen_true(s + start);
	res = ft_calloc_gnl(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	if (start != 0)
		free(s);
	if (res[0] == '\0')
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (&*dest);
}
