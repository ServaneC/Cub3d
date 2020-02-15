/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 08:44:19 by schene            #+#    #+#             */
/*   Updated: 2020/02/11 17:31:13 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		empty_l_map(char *join)
{
	int i;
	int s;

	i = 0;
	while (join[++i])
	{
		if (join[i - 1] == '\n' && join[i] == '\n' && i != 0)
		{
			s = i - 1;
			while (join[i] == '\n')
				i++;
			if (join[s - 1] == '1' && join[i] == '1')
			{
				free(join);
				return (-1);
			}
		}
	}
	return (1);
}

int		fill_r(t_data *data, char *line)
{
	int		i;

	i = 1;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (ft_atoi((const char *)&line[i]) > 0)
		{
			data->win->w = ft_atoi((const char *)&line[i]);
			if (data->win->w > MAX_WIN_WIDTH)
				data->win->w = MAX_WIN_WIDTH;
			while (ft_isdigit(line[i]))
				i++;
			if (ft_atoi((const char *)&line[i]) > 0)
				data->win->h = ft_atoi((const char *)&line[i]);
			else
				return (-1);
			if (data->win->h > MAX_WIN_HEIGHT)
				data->win->h = MAX_WIN_HEIGHT;
			return (1);
		}
		return (-1);
	}
	return (-1);
}

int		fill_text(char **ptr, char *line)
{
	int		i;

	i = 2;
	if (line[0] == 'S' && line[1] == ' ')
		i = 1;
	while (line[i] == ' ')
		i++;
	if (*ptr == NULL && !(*ptr = (char *)malloc(sizeof(char)
		* (ft_strlen(line) - i) + 1)))
		return (-1);
	ft_memcpy(*ptr, &line[i], ft_strlen(line));
	return (1);
}

int		fill_textures(t_data *data, char *line)
{
	int		rtn;

	rtn = 1;
	if (line[0] == 'S' && line[1] == ' ')
		rtn *= fill_text(&data->color->textures[4], line);
	else if (line[0] == 'N' && line[1] == 'O')
		rtn *= fill_text(&data->color->textures[0], line);
	else if (line[0] == 'S' && line[1] == 'O')
		rtn *= fill_text(&data->color->textures[1], line);
	else if (line[0] == 'W' && line[1] == 'E')
		rtn *= fill_text(&data->color->textures[3], line);
	else if (line[0] == 'E' && line[1] == 'A')
		rtn *= fill_text(&data->color->textures[2], line);
	else
		return (-1);
	return (rtn);
}

int		fill_colors(t_data *data, char *line, int i)
{
	t_rgb	cl;

	if ((cl.r = ft_atoi(&line[i])) >= 0)
	{
		while (ft_isdigit(line[i]) || line[i] == ' ')
			i++;
		if (line[i] == ',' && (cl.g = ft_atoi(&line[++i])) >= 0)
		{
			while (ft_isdigit(line[i]) || line[i] == ' ')
				i++;
			if (line[i] == ',' && (cl.b = ft_atoi(&line[++i])) >= 0)
			{
				while (ft_isdigit(line[i]) || line[i] == ' ')
					i++;
				if (line[0] == 'F' && line[i] == 0)
					data->color->f = ft_color_convert(cl.r, cl.g, cl.b);
				else if (line[0] == 'C' && line[i] == 0)
					data->color->c = ft_color_convert(cl.r, cl.g, cl.b);
				else
					return (-1);
				return (1);
			}
		}
	}
	return (-1);
}
