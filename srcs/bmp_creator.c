/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 07:37:21 by schene            #+#    #+#             */
/*   Updated: 2020/02/12 13:29:13 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	int_in_header(int nb, unsigned char *ptr)
{
	ptr[0] = (unsigned char)nb;
	ptr[1] = (unsigned char)(nb >> 8);
	ptr[2] = (unsigned char)(nb >> 16);
	ptr[2] = (unsigned char)(nb >> 24);
}

int		write_bmp_header(t_data *data, int fd, int f_size)
{
	unsigned char	header[54];
	int				i;

	i = -1;
	while (++i < 54)
		header[i] = (unsigned char)'\0';
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	int_in_header(f_size, &header[2]);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	int_in_header(data->win->w, &header[18]);
	int_in_header(data->win->h, &header[22]);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	return (write(fd, header, 54));
}

int		write_color(int pxl, int fd)
{
	unsigned char	color[3];

	color[0] = (unsigned char)(pxl);
	color[1] = (unsigned char)(pxl >> 8);
	color[2] = (unsigned char)(pxl >> 16);
	if (write(fd, color, 3) == -1)
		return (0);
	return (1);
}

int		write_bmp_data(t_data *data, int fd, int pad)
{
	int		y;
	int		x;
	char	null;
	int		pxl;

	null = 0;
	y = data->win->h;
	while (--y > -1)
	{
		x = -1;
		while (++x < data->win->w && pxl != -1)
		{
			pxl = data->img->data_img[data->win->w * y + x];
			if (!write_color(pxl, fd))
				return (-1);
		}
		x = -1;
		while (++x < pad && pxl != -1)
			pxl = write(fd, &null, 1);
		if (pxl == -1)
			return (-1);
	}
	return (1);
}

void	create_bmp(t_data *data)
{
	int		fd;
	int		f_size;
	int		pad;

	if ((fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND)) < 0)
		ft_error(data, BMP_ER);
	pad = (4 - ((3 * data->win->w) % 4)) % 4;
	f_size = 54 + (3 * data->win->w * data->win->h) + (pad * data->win->w);
	if (write_bmp_header(data, fd, f_size) == -1)
		ft_error(data, BMP_ER);
	if (write_bmp_data(data, fd, pad) == -1)
		ft_error(data, BMP_ER);
	close(fd);
	quit_program((void *)data);
}
