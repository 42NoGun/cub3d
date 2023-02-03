/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:24:18 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 16:54:28 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_window(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		free_rest(data);
		mlx_destroy_window(data->mlx->display, data->mlx->window);
		system("leaks cub3D");
		exit(0);
	}
}

int	win_close(t_data *data)
{
	free_rest(data);
	mlx_destroy_window(data->mlx->display, data->mlx->window);
	system("leaks cub3D");
	exit(0);
}
