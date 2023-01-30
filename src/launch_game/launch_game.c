/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:40 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/30 17:10:03 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// draw rendered image buffer to screen in current state
static void	draw_image_to_screen(t_data *data)
{
	const t_mlx	*mlx = data->mlx;

	mlx_put_image_to_window(mlx->display, mlx->window, mlx->image->img, 0, 0);
}

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
			// ret = mlx->addr + (y * mlx->size_line
			// 		+ x * (mlx->bits_per_pixel / 8));
			if (y < middle_line)
				put_pixel_to_image(mlx->image, x, y, data->color->ceilling_color);
				// *((unsigned int *)ret) = data->color->ceilling_color;
			else
				put_pixel_to_image(mlx->image, x, y, data->color->floor_color);
				// *((unsigned int *)ret) = data->color->floor_color;
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

void	launch_game(t_data *data)
{
	render_map(data);
	draw_image_to_screen(data);
	mlx_loop(data->mlx->display);
}
