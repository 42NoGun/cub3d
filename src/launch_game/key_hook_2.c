/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:24:18 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 14:42:36 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_window(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		//free
		mlx_destroy_window(data->mlx->display, data->mlx->window);
		exit(0);
	}
}

int	win_close(t_data *data)
{
	//free
	mlx_destroy_window(data->mlx->display, data->mlx->window);
	exit(0);
}
