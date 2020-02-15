/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:26:05 by schene            #+#    #+#             */
/*   Updated: 2020/02/14 13:59:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY ||
		key == LEFT_KEY || key == RIGHT_KEY)
		data->key->press = 1;
	if (key == W_KEY)
		data->key->front = 1;
	else if (key == S_KEY)
		data->key->back = 1;
	else if (key == A_KEY)
		data->key->left = 1;
	else if (key == D_KEY)
		data->key->right = 1;
	if (key == LEFT_KEY)
		data->key->rot_l = 1;
	else if (key == RIGHT_KEY)
		data->key->rot_r = 1;
	else if (key == ESC_KEY)
	{
		free_memory(data);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int		key_release(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == W_KEY)
		data->key->front = 0;
	else if (key == S_KEY)
		data->key->back = 0;
	else if (key == A_KEY)
		data->key->left = 0;
	else if (key == D_KEY)
		data->key->right = 0;
	if (key == LEFT_KEY)
		data->key->rot_l = 0;
	else if (key == RIGHT_KEY)
		data->key->rot_r = 0;
	if (data->key->front == 0 && data->key->back == 0 && data->key->left == 0
		&& data->key->right == 0 && data->key->rot_l == 0
			&& data->key->rot_r == 0)
		data->key->press = 0;
	return (1);
}
