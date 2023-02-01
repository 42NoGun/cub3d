/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:59:53 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 16:20:19 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	caculate_init_dist(t_data *data, t_raycast *cur_state)
{
	if (cur_state->raydir_x < 0)
	{
		cur_state->step_x = -1;
		cur_state->sidedist_x = (data->player->pos_x - cur_state->map_x)
			* cur_state->deltadist_x;
	}
	else
	{
		cur_state->step_x = 1;
		cur_state->sidedist_x = (cur_state->map_x + 1.0 - data->player->pos_x)
			* cur_state->deltadist_x;
	}
	if (cur_state->raydir_y < 0)
	{
		cur_state->step_y = -1;
		cur_state->sidedist_y = (data->player->pos_y - cur_state->map_y)
			* cur_state->deltadist_y;
	}
	else
	{
		cur_state->step_y = 1;
		cur_state->sidedist_y = (cur_state->map_y + 1.0 - data->player->pos_y)
			* cur_state->deltadist_y;
	}
}

static void	init_cur_state(t_data *data, t_raycast *cur_state, int x)
{
	const t_player	*player = data->player;

	cur_state->ratio = 2 * x / (double)SCREEN_WIDTH - 1;
	cur_state->raydir_x = player->dir_x + player->plane_x * cur_state->ratio;
	cur_state->raydir_y = player->dir_y + player->plane_y * cur_state->ratio;
	cur_state->map_x = (int)player->pos_x;
	cur_state->map_y = (int)player->pos_y;
	if (cur_state->raydir_x == 0)
		cur_state->deltadist_x = 1e30;
	else
		cur_state->deltadist_x = fabs(1 / cur_state->raydir_x);
	if (cur_state->raydir_y == 0)
		cur_state->deltadist_y = 1e30;
	else
		cur_state->deltadist_y = fabs(1 / cur_state->raydir_y);
	cur_state->hit = 0;
	caculate_init_dist(data, cur_state);
}

// if side == 1, hit y = c
// if side == 0, hit x = c
static void	dda(t_data *data, t_raycast *cur_state)
{
	while (cur_state->hit == 0)
	{
		if (cur_state->sidedist_x < cur_state->sidedist_y)
		{
			cur_state->sidedist_x += cur_state->deltadist_x;
			cur_state->map_x += cur_state->step_x;
			cur_state->side = 0;
		}
		else
		{
			cur_state->sidedist_y += cur_state->deltadist_y;
			cur_state->map_y += cur_state->step_y;
			cur_state->side = 1;
		}
		if (data->map->world_map[cur_state->map_y][cur_state->map_x] == '1')
			cur_state->hit = 1;
	}
}

static void	get_line_height(t_raycast *cur_state)
{
	if (cur_state->side == 0)
		cur_state->walldist = (cur_state->sidedist_x - cur_state->deltadist_x); // 근근사사치  인인것  같같은  어어떤떤것것	
	else
		cur_state->walldist = (cur_state->sidedist_y - cur_state->deltadist_y);
	cur_state->line_height = (int)(SCREEN_HEIGHT / cur_state->walldist);
	cur_state->draw_start = SCREEN_HEIGHT / 2 - cur_state->line_height / 2;
	if (cur_state->draw_start < 0)
		cur_state->draw_start = 0;
	cur_state->draw_end = SCREEN_HEIGHT / 2 + cur_state->line_height / 2;
	if (cur_state->draw_end >= SCREEN_HEIGHT)
		cur_state->draw_end = SCREEN_HEIGHT - 1;
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
	tex_pos = 0.0;
	y = cur_state->draw_start;
	while (y < cur_state->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_color_from_texture(data->wall[cur_state->tex_num].image,
				cur_state, tex_y);
		put_pixel_to_image(data->mlx->image, x, y, color);
		++y;
	}
}

static void	draw_wall_to_image(t_data *data, t_raycast *cur_state, int x)
{
	get_tex_num(cur_state);
	get_real_hit_pos(data, cur_state);
	put_texture_line_to_image(data, cur_state, x);
}

static void	raycast(t_data *data)
{
	t_raycast	cur_state;
	int			x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_cur_state(data, &cur_state, x);
		dda(data, &cur_state);
		get_line_height(&cur_state);
		draw_wall_to_image(data, &cur_state, x);
		++x;
	}
}

// draw wall to image buffer in current player state
void	render_wall(t_data *data)
{
	raycast(data);
	return ;
}
