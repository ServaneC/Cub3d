/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:51:14 by schene            #+#    #+#             */
/*   Updated: 2019/10/18 12:57:54 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if (dstsize != 0 && (src != NULL && dst != NULL))
		dst = ft_strncpy(dst, src, dstsize - 1);
	return (ft_strlen(src));
}
