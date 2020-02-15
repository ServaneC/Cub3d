/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:13:13 by schene            #+#    #+#             */
/*   Updated: 2019/11/13 13:18:57 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_unsigned_nbr(int nb)
{
	unsigned int	n;

	n = nb;
	if (n >= 10)
	{
		ft_put_unsigned_nbr(n / 10);
		ft_putchar('0' + n % 10);
	}
	else
		ft_putchar(n + '0');
}
