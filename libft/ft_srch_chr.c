/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srch_chr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:39:18 by schene            #+#    #+#             */
/*   Updated: 2020/02/06 13:39:41 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_srch_chr(char *str, char *to_find)
{
	int		i;
	int		rtn;

	i = -1;
	rtn = 0;
	while (str[++i])
	{
		if (ft_strchr((const char *)to_find, (int)str[i]) != NULL)
			rtn++;
	}
	if (rtn == 1)
		return (1);
	return (0);
}
