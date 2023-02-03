/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanbkim <hanbkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:48:21 by hanbkim           #+#    #+#             */
/*   Updated: 2023/02/03 15:55:31 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_color_from_texture(t_image *image,
		t_raycast *cur_state, int tex_y)
{
	char	*color;

	color = image->addr
		+ (tex_y * image->size_line
			+ cur_state->tex_x * (image->bits_per_pixel / 8));
	return (*((unsigned int *)(color)));
}

static void	put_texture_line_to_image(t_data *data, t_raycast *cur_state, int x)
{
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;
	unsigned int	color;

	step = 1.0 * TEX_HEIGHT / cur_state->line_height;
	tex_pos = (cur_state->draw_start - SCREEN_HEIGHT / 2
			+ cur_state->line_height / 2) * step;
	y = cur_state->draw_start;
	while (y < cur_state->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_color_from_texture(data->wall[cur_state->tex_num].image,
				cur_state, tex_y);
		put_pixel_to_image(data->mlx->image, x, y, color);
		++y;
	}
}

// real tile position caculate fomula???
static void	get_real_hit_pos(t_data *data, t_raycast *cur_state)
{
	if (cur_state->side == 0)
	{
		cur_state->wall_x = data->player->pos_y
			+ cur_state->walldist * cur_state->raydir_y;
	}
	else
	{
		cur_state->wall_x = data->player->pos_x
			+ cur_state->walldist * cur_state->raydir_x;
	}
	cur_state->wall_x -= floor(cur_state->wall_x);
	cur_state->tex_x = (int)(cur_state->wall_x * (double)TEX_WIDTH);
	if (cur_state->side == 0 && cur_state->raydir_x < 0)
		cur_state->tex_x = TEX_WIDTH - cur_state->tex_x - 1;
	if (cur_state->side == 1 && cur_state->raydir_y > 0)
		cur_state->tex_x = TEX_WIDTH - cur_state->tex_x - 1;
}

static void	get_tex_num(t_raycast *cur_state)
{
	if (cur_state->side == 0)
	{
		if (cur_state->raydir_x < 0)
			cur_state->tex_num = 2;
		else
			cur_state->tex_num = 3;
	}
	else
	{
		if (cur_state->raydir_y < 0)
			cur_state->tex_num = 0;
		else
			cur_state->tex_num = 1;
	}
}

void	draw_wall_to_image(t_data *data, t_raycast *cur_state, int x)
{
	get_tex_num(cur_state);
	get_real_hit_pos(data, cur_state);
	put_texture_line_to_image(data, cur_state, x);
}
