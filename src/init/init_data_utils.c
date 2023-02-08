/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:45:06 by hanbkim           #+#    #+#             */
/*   Updated: 2023/02/08 17:02:52 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_dir(char c)
{
	if (c == 3 || c == 4 || c == 5 || c == 6)
		return (true);
	else
		return (false);
}

void	get_player_init_pos(t_player *player, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_dir(map->world_map[y][x]) == true)
			{
				player->init_state = map->world_map[y][x];
				player->pos_x = (double)x + 0.5;
				player->pos_y = (double)y + 0.5;
			}
			++x;
		}
		++y;
	}
}

void	get_player_init_dir(t_player *player)
{
	if (player->init_state == 6)
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	else if (player->init_state == 5)
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (player->init_state == 4)
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
}

void	get_player_init_plane(t_player *player)
{
	if (player->init_state == 6)
	{
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (player->init_state == 5)
	{
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (player->init_state == 4)
	{
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else
	{
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
}
