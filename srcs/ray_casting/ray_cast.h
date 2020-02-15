/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:55:12 by schene            #+#    #+#             */
/*   Updated: 2020/02/10 08:06:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H

# include "../cub3d.h"
# define NORTH 0
# define SOUTH 1
# define WEST 3
# define EAST 2

typedef struct	s_cast
{
	double		cam_x;
	t_coint		map;
	t_coord		ray;
	t_coord		c_side;
	t_coord		delta;
	double		wall_dist;
	t_coint		step;
	int			hit;
	int			side;
	int			w_dir;
	int			h_line;
}				t_cast;

typedef struct	s_draw
{
	int			wall_start;
	int			wall_end;
	double		wall_x;
	double		step;
	t_coint		tex;
	double		tex_pos;
}				t_draw;

void			cast_sprites(t_data *data, double z_buff[data->win->w]);
int				search_sprites(t_data *data);
int				sprites_nb(t_data *data);
int				draw_slice(t_data *data, t_cast *rcast, int x);

#endif
