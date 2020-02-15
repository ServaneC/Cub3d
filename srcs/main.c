/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:52:56 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 13:34:22 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			fill_textures_tabs(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (!(data->img->text_data[i] = (t_text *)malloc(sizeof(t_text))))
			return (EXIT_FAILURE);
		if ((data->img->textures_ptr[i] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->color->textures[i], &data->img->text_data[i]->w,
			&data->img->text_data[i]->h)) == NULL)
			return (EXIT_FAILURE);
		data->img->text_data[i]->data = (int *)mlx_get_data_addr(
			data->img->textures_ptr[i], &data->img->bpp,
			&data->img->size_l, &data->img->endian);
	}
	return (1);
}

void		init_ptr(t_data *data)
{
	int		i;

	data->map->array = NULL;
	data->pos->dir.x = 0.0;
	data->pos->dir.y = 0.0;
	data->map->h = 0;
	data->win->h = 0;
	data->win->w = 0;
	data->color->c = -1;
	data->color->f = -1;
	data->spr->sp = NULL;
	data->win->win_ptr = NULL;
	data->img->img_ptr = NULL;
	data->img->data_img = NULL;
	data->mlx_ptr = NULL;
	data->key->back = 0;
	data->key->front = 0;
	i = -1;
	while (++i < 5)
	{
		data->color->textures[i] = NULL;
		data->img->textures_ptr[i] = NULL;
		data->img->text_data[i] = NULL;
	}
}

t_data		*data_init(void)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(data->win = (t_win *)malloc(sizeof(t_win))))
		return (NULL);
	if (!(data->color = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	if (!(data->img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	if (!(data->pos = (t_pos *)malloc(sizeof(t_pos))))
		return (NULL);
	if (!(data->spr = (t_sprite *)malloc(sizeof(t_sprite))))
		return (NULL);
	if (!(data->key = (t_key *)malloc(sizeof(t_key))))
		return (NULL);
	init_ptr(data);
	data->key->left = 0;
	data->key->right = 0;
	data->key->rot_l = 0;
	data->key->rot_r = 0;
	data->key->press = 0;
	return (data);
}

void		main_fct(t_data *data, char *av1, int save)
{
	int		rtn;

	if ((rtn = parsing_map(av1, data)) != 1)
		ft_error_parsing(rtn, data);
	if ((data->mlx_ptr = mlx_init()) == NULL)
		ft_error_parsing(WIN_ER, data);
	if (fill_textures_tabs(data) == -1)
		ft_error(data, ER_TEXT);
	if ((data->win->win_ptr = mlx_new_window(
			data->mlx_ptr, data->win->w, data->win->h, "Cub3d")) == NULL)
		ft_error(data, ER);
	if ((data->img->img_ptr = mlx_new_image(
			data->mlx_ptr, data->win->w, data->win->h)) == NULL)
		ft_error(data, ER);
	data->img->data_img = (int *)mlx_get_data_addr(data->img->img_ptr,
		&data->img->bpp, &data->img->size_l, &data->img->endian);
	if (ray_cast(data) == -1)
		ft_error(data, R_CAST);
	if (save == 1)
		create_bmp(data);
}

int			main(int ac, char **av)
{
	t_data	*data;
	int		save;

	save = 0;
	data = NULL;
	if (ac != 2 && ac != 3)
		ft_error(data, NO_FILE);
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", (int)ft_strlen(av[2])) == 0)
			save = 1;
		else
			ft_error(data, WR_ARG);
	}
	data = data_init();
	main_fct(data, av[1], save);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win->win_ptr, data->img->img_ptr, 0, 0);
	mlx_hook(data->win->win_ptr, KEYPRESS, (1L << 0), key_press, (void *)data);
	mlx_hook(data->win->win_ptr, KEYREL, (1L << 1), key_release, (void *)data);
	mlx_hook(data->win->win_ptr, DESTROYNOTIFY, (1L << 17),
		quit_program, (void *)data);
	mlx_loop_hook(data->mlx_ptr, do_mvmnt, (void *)data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
