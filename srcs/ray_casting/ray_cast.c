/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:44:21 by schene            #+#    #+#             */
/*   Updated: 2020/02/11 18:43:28 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

t_cast	*rcast_init(t_data *data)
{
	t_cast	*rcast;

	if (!(rcast = (t_cast *)malloc(sizeof(t_cast))))
		return (NULL);
	data->pos->plane.x = 0.0;
	data->pos->plane.y = 0.0;
	data->pos->plane.x = (double)(-0.66 * data->pos->dir.y);
	data->pos->plane.y = (double)(0.66 * data->pos->dir.x);
	if (search_sprites(data) == -1)
		return (NULL);
	return (rcast);
}

void	init_loop(t_cast *rcast, t_data *data, int x)
{
	rcast->map.x = (int)data->pos->p.x;
	rcast->map.y = (int)data->pos->p.y;
	rcast->cam_x = 2 * x / (double)(data->win->w) - 1.0;
	rcast->ray.x = (double)(data->pos->dir.x
		+ data->pos->plane.x * rcast->cam_x);
	rcast->ray.y = (double)(data->pos->dir.y
		+ data->pos->plane.y * rcast->cam_x);
	rcast->delta.x = fabs(1 / rcast->ray.x);
	rcast->delta.y = fabs(1 / rcast->ray.y);
	rcast->hit = 0;
	if (rcast->ray.x < 0)
		rcast->c_side.x = (data->pos->p.x - rcast->map.x) * rcast->delta.x;
	else
		rcast->c_side.x = (rcast->map.x + 1.0 - data->pos->p.x)
			* rcast->delta.x;
	if (rcast->ray.y < 0)
		rcast->c_side.y = (data->pos->p.y - rcast->map.y) * rcast->delta.y;
	else
		rcast->c_side.y = (rcast->map.y + 1.0 - data->pos->p.y)
			* rcast->delta.y;
}

void	find_intersection(t_cast *rcast, t_data *data)
{
	rcast->side = 0;
	rcast->step.x = 1;
	rcast->step.y = 1;
	if (rcast->ray.x < 0)
		rcast->step.x = -1;
	if (rcast->ray.y < 0)
		rcast->step.y = -1;
	while (rcast->hit == 0)
	{
		if (rcast->c_side.x < rcast->c_side.y)
		{
			rcast->c_side.x += rcast->delta.x;
			rcast->map.x += rcast->step.x;
			rcast->side = 1;
		}
		else
		{
			rcast->c_side.y += rcast->delta.y;
			rcast->map.y += rcast->step.y;
			rcast->side = 0;
		}
		if (data->map->array[rcast->map.y][rcast->map.x] == '1')
			rcast->hit = 1;
	}
}

double	find_walldst(t_cast *rcast, t_data *data)
{
	if (rcast->side == 1)
		return (fabs((rcast->map.x - data->pos->p.x +
			(1.0 - rcast->step.x) / 2) / rcast->ray.x));
	else
		return (fabs((rcast->map.y - data->pos->p.y +
			(1.0 - rcast->step.y) / 2) / rcast->ray.y));
}

int		ray_cast(t_data *data)
{
	t_cast		*rcast;
	double		z_buff[data->win->w];
	int			x;

	x = 0;
	if ((rcast = rcast_init(data)) == NULL)
		return (-1);
	while (++x < data->win->w)
	{
		init_loop(rcast, data, x);
		find_intersection(rcast, data);
		rcast->wall_dist = find_walldst(rcast, data);
		rcast->h_line = (int)(data->win->h / rcast->wall_dist);
		z_buff[x] = rcast->wall_dist;
		if (draw_slice(data, rcast, x) == -1)
		{
			free(rcast);
			return (-1);
		}
	}
	free(rcast);
	cast_sprites(data, z_buff);
	free(data->spr->sp);
	return (1);
}
