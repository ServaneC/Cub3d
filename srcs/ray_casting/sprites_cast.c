/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:56:14 by schene            #+#    #+#             */
/*   Updated: 2020/02/10 09:51:23 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

int		search_sprites(t_data *data)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	data->spr->nb_sprites = sprites_nb(data);
	if (!(data->spr->sp =
		(t_coord *)malloc(sizeof(t_coord) * data->spr->nb_sprites)))
		return (-1);
	x = -1;
	while (++x < data->map->w)
	{
		y = -1;
		while (++y < data->map->h)
		{
			if (data->map->array[y][x] == '2')
			{
				data->spr->sp[++i].x = x + 0.5;
				data->spr->sp[i].y = y + 0.5;
			}
		}
	}
	return (1);
}

void	sort_sprites(t_data *data, int nb_sp, int i)
{
	int		j;
	double	sp_distance[data->spr->nb_sprites];
	int		sp_order[data->spr->nb_sprites];

	j = -1;
	while (++j < data->spr->nb_sprites)
	{
		sp_order[j] = j;
		sp_distance[j] = ((data->pos->p.x - data->spr->sp[j].x) * (data->pos
			->p.x - data->spr->sp[j].x) + (data->pos->p.y - data->spr->sp[j].y)
			* (data->pos->p.y - data->spr->sp[j].y));
	}
	j = 1;
	while (j < nb_sp)
	{
		if (sp_distance[j - 1] < sp_distance[j])
		{
			ft_swap_dbl(&sp_distance[j - 1], &sp_distance[j]);
			ft_swap(&sp_order[j - 1], &sp_order[j]);
			j = 0;
		}
		j++;
	}
	data->spr->spr.x = data->spr->sp[sp_order[i]].x - data->pos->p.x;
	data->spr->spr.y = data->spr->sp[sp_order[i]].y - data->pos->p.y;
}

int		set_sprite(t_data *data, int i)
{
	sort_sprites(data, data->spr->nb_sprites, i);
	data->spr->inv_coef = 1.0 / (data->pos->plane.x * data->pos->dir.y -
		data->pos->dir.x * data->pos->plane.y);
	data->spr->trans.x = data->spr->inv_coef * (data->pos->dir.y *
		data->spr->spr.x - data->pos->dir.x * data->spr->spr.y);
	data->spr->trans.y = data->spr->inv_coef * (-data->pos->plane.y *
		data->spr->spr.x + data->pos->plane.x * data->spr->spr.y);
	data->spr->sp_win_x = (int)((data->win->w / 2) *
		(1 + data->spr->trans.x / data->spr->trans.y));
	data->spr->h_spr = abs((int)(data->win->h / data->spr->trans.y));
	data->spr->start.y = -data->spr->h_spr / 2 + data->win->h / 2;
	if (data->spr->start.y < 0)
		data->spr->start.y = 0;
	data->spr->end.y = data->spr->h_spr / 2 + data->win->h / 2;
	if (data->spr->end.y >= data->win->h)
		data->spr->end.y = data->win->h - 1;
	data->spr->w_spr = abs((int)(data->win->h / data->spr->trans.y));
	data->spr->start.x = -data->spr->w_spr / 2 + data->spr->sp_win_x;
	if (data->spr->start.x < 0)
		data->spr->start.x = 0;
	data->spr->end.x = data->spr->w_spr / 2 + data->spr->sp_win_x;
	if (data->spr->end.x >= data->win->w)
		data->spr->end.x = data->win->w - 1;
	return (data->spr->start.x - 1);
}

void	if_cast_sprites(t_data *data, int s)
{
	int		y;
	int		d;
	int		clr;

	y = data->spr->start.y - 1;
	while (++y < data->spr->end.y)
	{
		d = y * 256 - data->win->h * 128 + data->spr->h_spr * 128;
		data->spr->text.y = ((d * data->img->text_data[4]->h)
			/ data->spr->h_spr) / 256;
		clr = data->img->text_data[4]->data[data->img->text_data[4]
			->w * data->spr->text.y + data->spr->text.x];
		if (clr != 0x0)
			data->img->data_img[data->win->w * y + s] = clr;
	}
}

void	cast_sprites(t_data *data, double z_buff[data->win->w])
{
	int		i;
	int		s;

	i = -1;
	while (++i < data->spr->nb_sprites)
	{
		s = set_sprite(data, i);
		while (++s < data->spr->end.x)
		{
			data->spr->text.x = (int)(256 * (s - (-data->spr->w_spr / 2 +
				data->spr->sp_win_x)) * data->img->text_data[4]->w /
					data->spr->w_spr) / 256;
			if (data->spr->trans.y > 0 && s > 0 && s < data->win->w &&
				data->spr->trans.y < z_buff[s])
				if_cast_sprites(data, s);
		}
	}
}
