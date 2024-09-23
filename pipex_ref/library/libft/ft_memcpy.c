/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:58:38 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/07 16:08:56 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*temp_d;
	const unsigned char	*temp_s;

	if (src == 0 && dst == 0)
		return (dst);
	temp_d = (unsigned char *) dst;
	temp_s = (const unsigned char *) src;
	while (n > 0)
	{
		*temp_d++ = *temp_s++;
		n--;
	}
	return (dst);
}
