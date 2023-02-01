/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:21:56 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 17:02:39 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	translate(int keycode, t_data *data)
// {
// 	if (keycode == D)
// 		data->var->x_translate += 10;
// 	else if (keycode == A)
// 		data->var->x_translate -= 10;
// 	else if (keycode == S)
// 		data->var->y_translate += 10;
// 	else if (keycode == W)
// 		data->var->y_translate -= 10;
// }

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
		data->player->angle = -M_PI / 180.0;
	else if (keycode == RIGHT)
		data->player->angle = M_PI / 180.0;
	rotate_z(&data->player->dir_x, &data->player->dir_y, data->player->angle);
	rotate_z(&data->player->plane_x, &data->player->plane_y, data->player->angle);
}

int	key_hook(int keycode, t_data *data)
{
	// if (keycode == D || keycode == A || keycode == S || keycode == W)
	// 	translate(keycode, data);
	if (keycode == LEFT || keycode == RIGHT)
		rotate(keycode, data);
	else if (keycode == ESC)
		exit_window(keycode, data);
	printf("player angle : %f\n", data->player->angle);
	return (0);
}
