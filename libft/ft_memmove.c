/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:46:08 by schene            #+#    #+#             */
/*   Updated: 2019/10/24 15:42:24 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*s;

	dest = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = 0;
	if (s < dest)
		while (++i <= len)
			dest[len - i] = s[len - i];
	else
		while (len-- > 0)
			*(dest++) = *(s++);
	return (dst);
}
