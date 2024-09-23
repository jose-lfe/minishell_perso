/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:54:54 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/07 16:08:50 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp_d;
	const unsigned char	*temp_s;

	temp_d = (unsigned char *) dst;
	temp_s = (const unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (dst);
	if (temp_d < temp_s)
	{
		while (len--)
			*temp_d++ = *temp_s++;
	}
	else
	{
		temp_d += len;
		temp_s += len;
		while (len--)
			*--temp_d = *--temp_s;
	}
	return (dst);
}
