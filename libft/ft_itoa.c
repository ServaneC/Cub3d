/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:40:44 by schene            #+#    #+#             */
/*   Updated: 2019/12/09 13:54:57 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_malloc(int n)
{
	int			size;
	long int	cmp;
	long int	nb;

	size = 0;
	cmp = 10;
	nb = n;
	if (nb < 0)
	{
		size++;
		nb *= -1;
	}
	if (nb > 1000000000)
		size++;
	while (cmp < 1000000000)
	{
		if (nb < cmp)
			return (size + 1);
		size++;
		cmp *= 10;
	}
	return (size + 1);
}

static void	fill_rtn(int n, char *rtn, int size)
{
	int			i;
	long int	nb;

	i = size;
	nb = n;
	if (nb < 0)
	{
		rtn[0] = '-';
		nb *= -1;
	}
	if (nb >= 10)
	{
		rtn[i] = '0' + nb % 10;
		i--;
		fill_rtn(nb / 10, rtn, i);
	}
	else
		rtn[i] = '0' + nb;
}

char		*ft_itoa(int n)
{
	char	*rtn;
	int		size;

	size = size_malloc(n);
	if (!(rtn = malloc(sizeof(char) * size + 1)))
		return (NULL);
	rtn[size] = '\0';
	fill_rtn(n, rtn, size - 1);
	return (rtn);
}
