/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:40 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 14:39:39 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// draw floor & ceilling to image buffer
static void	render_background(t_data *data)
{
	const t_mlx	*mlx = data->mlx;
	int			x;
	int			y;
	int			middle_line;

	y = 0;
	middle_line = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < middle_line)
				put_pixel_to_image(mlx->image, x, y, data->color->ceilling_color);
			else
				put_pixel_to_image(mlx->image, x, y, data->color->floor_color);
			++x;
		}
		++y;
	}
}

// rendering map to image buffer
static void	render_map(t_data *data)
{
	render_background(data);
	render_wall(data);
}

// draw rendered image buffer to screen in current state
static int	draw_image_to_screen(t_data *data)
{
	const t_mlx	*mlx = data->mlx;

	render_map(data);
	mlx_put_image_to_window(mlx->display, mlx->window, mlx->image->img, 0, 0);
	return (0);
}

//mlx_loop_hook() 사용해서 rendering 하기
void	launch_game(t_data *data)
{
	mlx_loop_hook(data->mlx->display, draw_image_to_screen, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_hook(data->mlx->window, 17, 0, win_close, data);
	mlx_loop(data->mlx->display);
}
