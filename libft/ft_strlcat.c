/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:02:51 by schene            #+#    #+#             */
/*   Updated: 2019/10/18 12:57:43 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (dest[i])
		i++;
	while (src[n] && n < nb)
	{
		dest[i] = src[n];
		i++;
		n++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	if (src == NULL || dst == NULL)
		return (0);
	if (dstsize <= ft_strlen(dst))
		size = ft_strlen(src) + dstsize;
	else
	{
		size = ft_strlen(dst) + ft_strlen(src);
		dstsize = dstsize - ft_strlen(dst) - 1;
		dst = ft_strncat(dst, src, dstsize);
	}
	return (size);
}
