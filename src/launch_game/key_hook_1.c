/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:21:56 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/08 17:03:02 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_dir(int keycode, t_data *data, double dir_x, double dir_y)
{
	double	sign;
	int		x;
	int		y;

	sign = 0.0;
	if (keycode == W || keycode == D)
		sign = 1.0;
	else if (keycode == S || keycode == A)
		sign = -1.0;
	x = (int)(data->player->pos_x + dir_x * 0.51 * sign);
	y = (int)(data->player->pos_y + dir_y * 0.51 * sign);
	if (data->map->world_map[(int)data->player->pos_y][x] != 1)
		data->player->pos_x += dir_x * 0.51 * sign;
	if (data->map->world_map[y][(int)data->player->pos_x] != 1)
		data->player->pos_y += dir_y * 0.51 * sign;
}

void	translate(int keycode, t_data *data)
{
	if (keycode == W || keycode == S)
		move_dir(keycode, data, data->player->dir_x, data->player->dir_y);
	else if (keycode == D || keycode == A)
		move_dir(keycode, data, data->player->plane_x, data->player->plane_y);
}

void	rotate_z(double *x, double *y, double angle_z)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = cos(angle_z) * prev_x - sin(angle_z) * prev_y;
	*y = sin(angle_z) * prev_x + cos(angle_z) * prev_y;
}

void	rotate(int keycode, t_data *data)
{
	if (keycode == LEFT)
	{
		rotate_z(&data->player->dir_x, &data->player->dir_y, -M_PI / 18.0);
		rotate_z(&data->player->plane_x, &data->player->plane_y, -M_PI / 18.0);
	}
	else if (keycode == RIGHT)
	{
		rotate_z(&data->player->dir_x, &data->player->dir_y, M_PI / 18.0);
		rotate_z(&data->player->plane_x, &data->player->plane_y, M_PI / 18.0);
	}
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == D || keycode == A || keycode == S || keycode == W)
		translate(keycode, data);
	else if (keycode == LEFT || keycode == RIGHT)
		rotate(keycode, data);
	else if (keycode == ESC)
		exit_window(keycode, data);
	return (0);
}
