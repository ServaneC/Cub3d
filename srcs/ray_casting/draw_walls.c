/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:18:53 by schene            #+#    #+#             */
/*   Updated: 2020/02/12 12:07:52 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

void	wall_orientation(t_cast *rcast, t_data *data, t_draw *draw)
{
	if (rcast->side == 1)
	{
		draw->wall_x = data->pos->p.y + rcast->wall_dist * rcast->ray.y;
		rcast->w_dir = WEST;
		if (rcast->ray.x < 0)
			rcast->w_dir = EAST;
	}
	else
	{
		draw->wall_x = data->pos->p.x + rcast->wall_dist * rcast->ray.x;
		rcast->w_dir = NORTH;
		if (rcast->ray.y < 0)
			rcast->w_dir = SOUTH;
	}
	draw->wall_x -= floor(draw->wall_x);
}

t_draw	*init_draw(t_cast *rcast, t_data *data)
{
	t_draw	*draw;

	if (!(draw = (t_draw *)malloc(sizeof(t_draw))))
		return (NULL);
	wall_orientation(rcast, data, draw);
	draw->tex.x = (int)(draw->wall_x * data->img->text_data[rcast->w_dir]->w);
	if ((rcast->side == 0 && rcast->ray.x > 0) ||
		(rcast->side == 1 && rcast->ray.y < 0))
		draw->tex.x = data->img->text_data[rcast->w_dir]->w - draw->tex.x - 1;
	if (rcast->h_line < 0)
		rcast->h_line = data->win->h - 1;
	draw->wall_start = -rcast->h_line / 2 + data->win->h / 2;
	if (draw->wall_start < 0)
		draw->wall_start = 0;
	draw->wall_end = rcast->h_line / 2 + data->win->h / 2;
	draw->step = 1.0 * data->img->text_data[rcast->w_dir]->h / rcast->h_line;
	draw->tex_pos = (draw->wall_start - data->win->h / 2 +
		rcast->h_line / 2) * draw->step;
	if (draw->wall_end < 0 || draw->wall_end > data->win->h)
		draw->wall_end = data->win->h - 1;
	return (draw);
}

int		draw_slice(t_data *data, t_cast *rcast, int x)
{
	t_draw	*draw;
	int		y;
	int		idx;

	if ((draw = init_draw(rcast, data)) == NULL)
		return (-1);
	y = -1;
	while (++y < draw->wall_start)
		data->img->data_img[data->win->w * y + x] = data->color->c;
	y--;
	while (++y < draw->wall_end)
	{
		draw->tex.y = (int)(draw->tex_pos);
		draw->tex_pos += draw->step;
		if ((idx = data->win->w * y + x) >= data->win->h * data->win->w)
			idx = data->win->h * data->win->w;
		data->img->data_img[idx] = data->img->text_data[rcast->w_dir]->data
			[data->img->text_data[rcast->w_dir]->w * draw->tex.y + draw->tex.x];
	}
	free(draw);
	y--;
	while (++y < data->win->h)
		data->img->data_img[data->win->w * y + x] = data->color->f;
	return (1);
}
