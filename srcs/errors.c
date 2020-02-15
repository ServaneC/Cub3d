/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:39:17 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 14:19:17 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			quit_program(void *param)
{
	t_data *data;

	data = param;
	free_memory(data);
	exit(EXIT_SUCCESS);
}

void		free_textures(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (data->color->textures[i])
			free(data->color->textures[i]);
		if (data->img->textures_ptr[i])
			mlx_destroy_image(data->mlx_ptr, data->img->textures_ptr[i]);
		if (data->img->text_data[i])
			free(data->img->text_data[i]);
	}
}

void		free_memory(t_data *data)
{
	int		i;

	i = -1;
	if (data->img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	while (++i < data->map->h)
		free(data->map->array[i]);
	free(data->map->array);
	free(data->map);
	if (data->win->win_ptr)
	{
		mlx_clear_window(data->mlx_ptr, data->win->win_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win->win_ptr);
	}
	free(data->win);
	free_textures(data);
	free(data->color);
	free(data->img);
	free(data->pos);
	free(data->spr);
	free(data->key);
}

void		ft_error_parsing(int error, t_data *data)
{
	free_memory(data);
	ft_putstr_fd("Error\n", 2);
	if (error == WR_FILE)
		ft_putstr_fd("The file is not <filename>.cub\n", 2);
	if (error == CNT_OPEN)
		ft_putstr_fd("The program can't open the file\n", 2);
	if (error == ER_READ)
		ft_putstr_fd("The map shouldn't have empty lines\n", 2);
	if (error == ER_R)
		ft_putstr_fd("Something is wrong with the resolution\n", 2);
	if (error == ER_TEXT)
		ft_putstr_fd("Something is wrong with the textures\n", 2);
	if (error == ER_CF)
		ft_putstr_fd(
			"Something is wrong with the floor or/and ceiling color\n", 2);
	if (error == ER_MAP)
		ft_putstr_fd("The map is invalid\n", 2);
	if (error == ER_IN_FL)
		ft_putstr_fd("There is an error in the file\n", 2);
	if (error == WIN_ER)
		ft_putstr_fd("An error occur while creating the window\n", 2);
	exit(EXIT_FAILURE);
}

void		ft_error(t_data *data, int error)
{
	if (error == WR_ARG)
		ft_putstr_fd("Error\nWrong argument after filename\n", 2);
	else if (error == NO_FILE)
		ft_putstr_fd("Error\nNo file in argument or too much argument\n", 2);
	else
	{
		free_memory(data);
		if (error == ER)
			ft_putstr_fd("Error\nAn error occur\n", 2);
		if (error == R_CAST)
			ft_putstr_fd("Error\nAn error occur during the raycasting\n", 2);
		else if (error == ER_TEXT)
			ft_putstr_fd(
				"Error\nAn error occur while reading the textures\n", 2);
		else if (error == BMP_ER)
			ft_putstr_fd("Error\nThe bmp image couldn't be created\n", 2);
	}
	exit(EXIT_FAILURE);
}
