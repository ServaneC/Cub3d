/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:35:26 by schene            #+#    #+#             */
/*   Updated: 2020/02/12 12:02:45 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	f;
	int n;

	i = 0;
	f = 0;
	n = 1;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (-1);
	if ((!(str[i] >= '0' && str[i] <= '9')) && str[i])
		return (0);
	i--;
	while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
		f = (f * 10 + (str[i] - 48));
	return (f * n);
}
