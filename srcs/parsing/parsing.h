/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:13:38 by schene            #+#    #+#             */
/*   Updated: 2020/02/09 18:21:06 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

# define MAX_WIN_WIDTH 2559
# define MAX_WIN_HEIGHT 1439

typedef struct	s_cmp
{
	char		*before;
	char		*ln;
	char		*nx;

}				t_cmp;

typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

int				fill_r(t_data *data, char *line);
int				fill_textures(t_data *data, char *line);
int				fill_colors(t_data *data, char *line, int i);
int				empty_l_map(char *join);
int				only_one(char *str);
int				get_len_map(char **to_parse, int i);
int				check_line(char *str);
int				check_first_line(t_cmp *strs);
int				fill_map(t_data *data, char **to_parse, int i);

#endif
