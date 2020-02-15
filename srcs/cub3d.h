/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:36:21 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 14:19:37 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define STEP 0.15
# define ROT 80
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define KEYPRESS 2
# define KEYREL 3
# define DESTROYNOTIFY 17

# define WR_FILE -2
# define CNT_OPEN -3
# define ER_READ -4
# define ER_R -5
# define ER_TEXT -6
# define ER_CF -7
# define ER_MAP -8
# define ER_IN_FL -9
# define R_CAST -10
# define WIN_ER -11
# define ER -12
# define WR_FLG -13
# define BMP_ER -14
# define WR_ARG -15
# define NO_FILE -16

typedef struct	s_key
{
	int			press;
	int			front;
	int			back;
	int			left;
	int			right;
	int			rot_l;
	int			rot_r;
}				t_key;

typedef struct	s_win
{
	void		*win_ptr;
	int			w;
	int			h;
}				t_win;

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_coint
{
	int			x;
	int			y;
}				t_coint;

typedef struct	s_text
{
	int			*data;
	int			h;
	int			w;
}				t_text;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data_img;
	void		*textures_ptr[5];
	t_text		*text_data[5];
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_colors
{
	char		*textures[5];
	int			f;
	int			c;
}				t_color;

typedef struct	s_map
{
	char		**array;
	int			w;
	int			h;
}				t_map;

typedef struct	s_pos
{
	t_coord		p;
	t_coord		dir;
	t_coord		plane;
	double		old_dir_x;
	double		old_plane_x;
}				t_pos;

typedef struct	s_sprite
{
	t_coord		*sp;
	t_coord		spr;
	t_coord		trans;
	t_coint		start;
	t_coint		end;
	t_coint		text;
	int			nb_sprites;
	int			sp_win_x;
	int			h_spr;
	int			w_spr;
	double		inv_coef;
}				t_sprite;

typedef struct	s_data
{
	void		*mlx_ptr;
	t_map		*map;
	t_win		*win;
	t_color		*color;
	t_img		*img;
	t_pos		*pos;
	t_sprite	*spr;
	t_key		*key;
}				t_data;

void			get_pos(t_data *data);
int				ray_cast(t_data *data);

int				key_press(int key, void *param);
int				key_release(int key, void *param);
int				do_mvmnt(void *param);
int				fill_textures_tabs(t_data *data);
int				quit_program(void *param);
t_data			*data_init(void);

void			ft_error_parsing(int error, t_data *data);
void			free_memory(t_data *data);
void			ft_error_textures(t_data *data);
void			ft_error(t_data *data, int error);

int				parsing_map(const char *file, t_data *data);

void			create_bmp(t_data *data);

#endif
