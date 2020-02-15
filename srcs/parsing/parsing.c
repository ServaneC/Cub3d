/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 08:43:53 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 14:22:35 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#define BUFF_SIZE 10

char	**read_file(int fd)
{
	char	*join;
	char	*tmp;
	char	*buf;
	char	**tab;
	int		rtn;

	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (NULL);
	join = ft_strdup("\0");
	while ((rtn = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rtn] = '\0';
		tmp = ft_strjoin(join, buf);
		free(join);
		join = tmp;
	}
	close(fd);
	free(buf);
	if (empty_l_map(join) == -1)
		return (NULL);
	tab = ft_split(join, '\n');
	free(join);
	return (tab);
}

int		fill_struct_while(t_data *data, char **to_parse, int i)
{
	if (to_parse[i][0] == 'R')
	{
		if (fill_r(data, to_parse[i]) != 1)
			return (ER_R);
	}
	else if ((ft_isalpha(to_parse[i][0]) && ft_isalpha(to_parse[i][1])) ||
		to_parse[i][0] == 'S')
	{
		if (fill_textures(data, to_parse[i]) != 1)
			return (ER_TEXT);
	}
	else if (to_parse[i][0] == 'F' || to_parse[i][0] == 'C')
	{
		if (fill_colors(data, to_parse[i], 1) != 1)
			return (ER_CF);
	}
	else if (ft_isdigit(to_parse[i][0]))
	{
		if (fill_map(data, to_parse, i) != 1)
			return (ER_MAP);
		return (0);
	}
	else
		return (ER_IN_FL);
	return (1);
}

int		fill_struct(t_data *data, char **to_parse)
{
	int		i;
	int		fd;

	i = -1;
	while (to_parse[++i])
	{
		if ((fd = fill_struct_while(data, to_parse, i)) == 0)
			break ;
		else if (fd != 1)
			return (fd);
	}
	i = -1;
	while (++i < 5)
	{
		if ((fd = open(data->color->textures[i], O_RDONLY)) < 0)
			return (ER_TEXT);
		close(fd);
	}
	if (data->win->h <= 0)
		return (ER_R);
	else if (data->color->f == -1 || data->color->c == -1)
		return (ER_CF);
	else if (data->map->h == 0)
		return (ER_MAP);
	return (1);
}

int		check_file(char *file)
{
	char	*ptr;

	if ((ptr = ft_strnstr(file, ".cub", ft_strlen(file))) == NULL)
		return (WR_FILE);
	if (ptr[4] != '\0')
		return (WR_FILE);
	return (1);
}

int		parsing_map(const char *file, t_data *data)
{
	int		fd;
	char	**to_parse;
	int		i;
	int		rtn;

	i = -1;
	if (check_file((char *)file) != 1)
		return (WR_FILE);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (CNT_OPEN);
	if ((to_parse = read_file(fd)) == NULL)
		return (ER_READ);
	if ((rtn = fill_struct(data, to_parse)) != 1)
	{
		while (to_parse[++i])
			free(to_parse[i]);
		free(to_parse);
		return (rtn);
	}
	get_pos(data);
	while (to_parse[++i])
		free(to_parse[i]);
	free(to_parse);
	return (1);
}
