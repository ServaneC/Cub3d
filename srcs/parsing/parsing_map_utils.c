/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:44:27 by schene            #+#    #+#             */
/*   Updated: 2020/02/09 18:15:26 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		only_one(char *str)
{
	int	j;

	j = -1;
	while (str[++j])
	{
		if (str[j] != '1')
			return (0);
	}
	return (1);
}

int		get_len_map(char **to_parse, int i)
{
	int			len;
	char		*tmp;

	len = 0;
	while (to_parse[++i])
	{
		if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(to_parse[i]))))
			return (-1);
		ft_remove_sp(to_parse[i], tmp);
		if ((int)ft_strlen(tmp) > len)
			len = (int)ft_strlen(tmp);
		free(tmp);
	}
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(to_parse[--i]))))
		return (-1);
	ft_remove_sp(to_parse[i], tmp);
	if (!only_one(tmp))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	if (len < 3)
		return (-1);
	return (len);
}

int		check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			i++;
		else
			return (0);
	}
	return (1);
}

int		check_first_line(t_cmp *strs)
{
	int	i;

	if (!only_one(strs->ln))
		return (-1);
	if (ft_strlen(strs->ln) < ft_strlen(strs->nx))
	{
		i = ft_strlen(strs->ln);
		if (!only_one(&strs->nx[i]))
			return (-1);
	}
	return (1);
}
