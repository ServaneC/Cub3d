/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:41:13 by schene            #+#    #+#             */
/*   Updated: 2020/02/09 18:15:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*free_strs(t_cmp *strs)
{
	if (strs->before)
		free(strs->before);
	if (strs->ln)
		free(strs->ln);
	if (strs->nx)
		free(strs->nx);
	free(strs);
	return (NULL);
}

t_cmp	*init_strs(int len, char **to_parse, int i, int idx)
{
	t_cmp *strs;

	if (!(strs = (t_cmp *)malloc(sizeof(t_cmp))))
		return (NULL);
	strs->before = NULL;
	strs->ln = NULL;
	strs->nx = NULL;
	if (!(strs->ln = (char *)malloc(sizeof(char) * len)))
		return (free_strs(strs));
	ft_remove_sp(to_parse[i], strs->ln);
	if (!(strs->nx = (char *)malloc(sizeof(char) * len)) || strs->ln[0] != '1')
		return (free_strs(strs));
	ft_remove_sp(to_parse[i + 1], strs->nx);
	if (idx == -1)
	{
		if (check_first_line(strs) == -1)
			return (free_strs(strs));
	}
	else if (idx != -1)
	{
		if (!(strs->before = (char *)malloc(sizeof(char) * len)))
			return (free_strs(strs));
		ft_remove_sp(to_parse[i - 1], strs->before);
	}
	return (strs);
}

char	*while_code(t_cmp *strs, int len, int idx)
{
	int		l_len;

	l_len = (int)ft_strlen(strs->ln);
	if (l_len > (int)ft_strlen(strs->nx))
	{
		if (!only_one(&strs->ln[(int)ft_strlen(strs->nx)]))
			return (NULL);
	}
	else if (idx != -1 && l_len > (int)ft_strlen(strs->before))
	{
		if (!only_one(&strs->ln[(int)ft_strlen(strs->before)]))
			return (NULL);
	}
	else if (strs->ln[(int)ft_strlen(strs->ln) - 1] != '1')
		return (NULL);
	l_len -= 2;
	while (++l_len < len)
		strs->ln[l_len] = '1';
	strs->ln[l_len] = '\0';
	if (!check_line(strs->ln))
		return (NULL);
	return ("SUCCESS");
}

char	*fill_line(t_data *data, char **to_parse, int i, int len)
{
	t_cmp	*strs;
	int		l_len;
	int		idx;

	idx = -1;
	while (to_parse[++i] && idx < data->map->h - 2)
	{
		if ((strs = init_strs(len, to_parse, i, idx)) == NULL)
			return (NULL);
		if (while_code(strs, len, idx) == NULL)
			return (free_strs(strs));
		data->map->array[++idx] = ft_strdup(strs->ln);
		free_strs(strs);
		if (data->map->array[idx] == NULL)
			return (NULL);
	}
	if (!(data->map->array[++idx] =
		(char *)malloc(sizeof(char) * data->map->w + 1)))
		return (NULL);
	ft_remove_sp(to_parse[i], data->map->array[idx]);
	l_len = (int)ft_strlen(data->map->array[idx]) - 2;
	while (++l_len < len)
		data->map->array[idx][l_len] = '1';
	return ("SUCCESS");
}

int		fill_map(t_data *data, char **to_parse, int i)
{
	int			idx;
	static int	pos;

	idx = i - 1;
	while (to_parse[++idx])
		data->map->h++;
	if (!(data->map->array = (char **)malloc(sizeof(char *) * data->map->h)))
		return (-1);
	idx = -1;
	while (++idx < data->map->h)
		data->map->array[idx] = NULL;
	if ((data->map->w = get_len_map(to_parse, i)) == -1)
		return (-1);
	if (fill_line(data, to_parse, --i, data->map->w) == NULL)
		return (-1);
	idx = -1;
	while (++idx < data->map->h)
	{
		if (ft_srch_chr(data->map->array[idx], "NSEW"))
			pos++;
	}
	if (pos != 1)
		return (-1);
	return (1);
}
