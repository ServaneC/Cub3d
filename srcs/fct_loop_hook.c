/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:35:54 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 13:50:25 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_front_back(t_data *data)
{
	if (data->key->front)
	{
		if (data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x + data->pos->dir.x * STEP)] != '1' &&
			data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x + data->pos->dir.x * STEP)] != '2')
			data->pos->p.x += STEP * data->pos->dir.x;
		if (data->map->array[(int)(data->pos->p.y + data->pos->dir.y * STEP)]
			[(int)data->pos->p.x] != '1' && data->map->array[(int)(data->pos
			->p.y + data->pos->dir.y * STEP)][(int)data->pos->p.x] != '2')
			data->pos->p.y += STEP * data->pos->dir.y;
	}
	else if (data->key->back)
	{
		if (data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x - data->pos->dir.x * STEP)] != '1'
			&& data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x - data->pos->dir.x * STEP)] != '2')
			data->pos->p.x -= STEP * data->pos->dir.x;
		if (data->map->array[(int)(data->pos->p.y - data->pos->dir.y * STEP)]
			[(int)data->pos->p.x] != '1' && data->map->array[(int)(data->pos->
			p.y - data->pos->dir.y * STEP)][(int)data->pos->p.x] != '2')
			data->pos->p.y -= STEP * data->pos->dir.y;
	}
}

void	step_side(t_data *data)
{
	if (data->key->left)
	{
		if (data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x + data->pos->dir.y * STEP)] != '1')
			data->pos->p.x += STEP * data->pos->dir.y;
		if (data->map->array[(int)(data->pos->p.y - data->pos->dir.x * STEP)]
			[(int)data->pos->p.x] != '1')
			data->pos->p.y -= STEP * data->pos->dir.x;
	}
	else if (data->key->right)
	{
		if (data->map->array[(int)data->pos->p.y]
			[(int)(data->pos->p.x - data->pos->dir.y * STEP)] != '1')
			data->pos->p.x -= STEP * data->pos->dir.y;
		if (data->map->array[(int)(data->pos->p.y + data->pos->dir.x * STEP)]
			[(int)data->pos->p.x] != '1')
			data->pos->p.y += STEP * data->pos->dir.x;
	}
}

void	left_rotation(t_data *data)
{
	data->pos->old_dir_x = data->pos->dir.x;
	data->pos->dir.x = data->pos->dir.x * cos(-(M_PI / ROT)) -
		data->pos->dir.y * sin(-(M_PI / ROT));
	data->pos->dir.y = data->pos->old_dir_x * sin(-(M_PI / ROT)) +
		data->pos->dir.y * cos(-(M_PI / ROT));
	data->pos->old_plane_x = data->pos->plane.x;
	data->pos->plane.x = data->pos->plane.x * cos(-(M_PI / ROT)) -
		data->pos->plane.y * sin(-(M_PI / ROT));
	data->pos->plane.y = data->pos->old_plane_x * sin(-(M_PI / ROT)) +
		data->pos->plane.y * cos(-(M_PI / ROT));
}

void	right_rotation(t_data *data)
{
	data->pos->old_dir_x = data->pos->dir.x;
	data->pos->dir.x = data->pos->dir.x * cos((M_PI / ROT))
		- data->pos->dir.y * sin((M_PI / ROT));
	data->pos->dir.y = data->pos->old_dir_x * sin((M_PI / ROT))
		+ data->pos->dir.y * cos((M_PI / ROT));
	data->pos->old_plane_x = data->pos->plane.x;
	data->pos->plane.x = data->pos->plane.x * cos((M_PI / ROT))
		- data->pos->plane.y * sin((M_PI / ROT));
	data->pos->plane.y = data->pos->old_plane_x * sin((M_PI / ROT))
		+ data->pos->plane.y * cos((M_PI / ROT));
}

int		do_mvmnt(void *param)
{
	t_data	*data;

	data = param;
	mlx_clear_window(data->mlx_ptr, data->win->win_ptr);
	if (data->key->front || data->key->back)
		step_front_back(data);
	else if (data->key->left || data->key->right)
		step_side(data);
	if (data->key->rot_l)
		left_rotation(data);
	else if (data->key->rot_r)
		right_rotation(data);
	if (ray_cast(data) == -1)
		ft_error(data, R_CAST);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win->win_ptr, data->img->img_ptr, 0, 0);
	return (1);
}
