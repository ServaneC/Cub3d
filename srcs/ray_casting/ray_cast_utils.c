/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:45:19 by schene            #+#    #+#             */
/*   Updated: 2020/02/10 08:07:02 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

void		get_pos(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->map->h)
	{
		x = -1;
		while (++x < data->map->w)
		{
			if (ft_isalpha(data->map->array[y][x]))
			{
				data->pos->p.x = x + 0.5;
				data->pos->p.y = y + 0.5;
				if (data->map->array[y][x] == 'N')
					data->pos->dir.y = -1.0;
				else if (data->map->array[y][x] == 'S')
					data->pos->dir.y = 1.0;
				else if (data->map->array[y][x] == 'E')
					data->pos->dir.x = 1.0;
				else if (data->map->array[y][x] == 'W')
					data->pos->dir.x = -1.0;
			}
		}
	}
}

int			sprites_nb(t_data *data)
{
	int		x;
	int		y;
	int		nb;

	nb = 0;
	x = -1;
	while (++x < data->map->w)
	{
		y = -1;
		while (++y < data->map->h)
		{
			if (data->map->array[y][x] == '2')
				nb++;
		}
	}
	return (nb);
}
