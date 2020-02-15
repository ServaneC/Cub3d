/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:21:43 by schene            #+#    #+#             */
/*   Updated: 2019/11/13 13:26:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_error(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (1);
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j] || base[i] == '+' || base[i] == '-')
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

static void		ft_putnbr_b(unsigned int n, char *base, unsigned int l)
{
	if (n < l)
		write(1, &base[n], 1);
	else
	{
		ft_putnbr_b((n / l), base, l);
		write(1, &base[n % l], 1);
	}
}

void			ft_putnbr_base(int nbr, char *base)
{
	unsigned int	n;
	unsigned int	l;

	n = nbr;
	l = ft_strlen((const char *)base);
	if (ft_error(base) == 1)
		return ;
	ft_putnbr_b(n, base, l);
}
