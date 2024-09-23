/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:03:43 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/06 11:38:28 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	r;
	char	*s;

	s = (char *)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	r = 0;
	i = 0;
	if (dstsize > dstlen)
		r = dstlen + srclen;
	else
		r = srclen + dstsize;
	while (s[i] != '\0' && dstlen + 1 < dstsize)
		dst[dstlen++] = s[i++];
	dst[dstlen] = '\0';
	return (r);
}
