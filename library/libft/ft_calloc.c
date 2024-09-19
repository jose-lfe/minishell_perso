/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:20:31 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/07 15:48:23 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	test;
	void	*res;

	if (count == 0 || size == 0)
		return (malloc(1));
	test = count * size;
	if (test / count != size)
		return (NULL);
	res = malloc(test);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, test);
	return (res);
}
