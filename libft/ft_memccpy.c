/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:10:41 by schene            #+#    #+#             */
/*   Updated: 2019/10/19 12:22:11 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;
	unsigned char	cmp;

	i = 0;
	d = dst;
	s = src;
	cmp = c;
	while (s[i] && i < n)
	{
		if (s[i] == c)
		{
			d[i] = s[i];
			i++;
			return (&d[i]);
		}
		d[i] = s[i];
		i++;
	}
	return (NULL);
}
