/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:52:29 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/01/30 13:45:46 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_check_line(char *stach);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_free(char *stach, int end, char *res);
char	*ft_strjoin_gnl(char *s1, char *s2);

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*res;
	static char	*stach[1000];
	int			end;

	end = BUFFER_SIZE;
	if (read(fd, 0, 0) != 0)
		end = -1;
	while (ft_check_line(stach[fd]) == 1 && end > 0)
	{
		buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		end = read(fd, buffer, BUFFER_SIZE);
		if (end > 0)
		{
			stach[fd] = ft_strjoin_gnl(stach[fd], buffer);
		}
		free(buffer);
	}
	res = ft_substr_gnl(stach[fd], 0, ft_strlen_gnl(stach[fd]));
	stach[fd] = ft_free(stach[fd], end, res);
	if (end >= 0 && read(fd, 0, 0) == 0)
		return (res);
	return (NULL);
}

int	ft_check_line(char *stach)
{
	int	i;

	i = 0;
	if (stach != NULL && stach[0] != '\0')
	{
		while (stach[i] != '\0')
		{
			if (stach[i] == '\n')
				return (0);
			i++;
		}
	}
	return (1);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (void *)malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

char	*ft_free(char *stach, int end, char *res)
{
	if (end <= 0)
	{
		free(stach);
		if (end == -1)
			free(res);
		return (NULL);
	}
	else
	{
		stach = ft_substr_gnl(stach, ft_strlen_gnl(stach), BUFFER_SIZE);
		return (stach);
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		j;
	int		i;
	char	*res;

	i = 0;
	if (s1 == NULL)
		return (ft_strdup_gnl(s2));
	res = malloc((ft_strlen_true(s1) + ft_strlen_true(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (s1 && s1[j] != '\0')
		res[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] != '\0')
		res[i++] = s2[j++];
	res[i] = '\0';
	if (s1)
		free(s1);
	return (res);
}
