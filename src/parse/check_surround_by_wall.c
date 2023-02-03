/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surround_by_wall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:24:22 by junji             #+#    #+#             */
/*   Updated: 2023/02/03 14:25:53 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_player_place_in_void(t_map_info *map_info, int i, int j)
{
	const int	east = j + 1;
	const int	west = j - 1;
	const int	south = i + 1;
	const int	north = i - 1;

	if (map_info->map[i][east] == -1)
		ft_terminate("usage: player must located in walls");
	if (map_info->map[i][west] == -1)
		ft_terminate("usage: player must located in walls");
	if (map_info->map[south][j] == -1)
		ft_terminate("usage: player must located in walls");
	if (map_info->map[north][j] == -1)
		ft_terminate("usage: player must located in walls");
}

static void	check_opened_wall(t_map_info *map_info, int i, int j)
{
	const int	east = j + 1;
	const int	west = j - 1;
	const int	south = i + 1;
	const int	north = i - 1;

	if (map_info->map[i][east] == -1)
		ft_terminate("usage: empty area must surrounded by walls");
	if (map_info->map[i][west] == -1)
		ft_terminate("usage: empty area must surrounded by walls");
	if (map_info->map[south][j] == -1)
		ft_terminate("usage: empty area must surrounded by walls");
	if (map_info->map[north][j] == -1)
		ft_terminate("usage: empty area must surrounded by walls");
}

static void	check_edge_is_empty(t_map_info *map_info, int i, int j)
{
	if (i == 0)
		ft_terminate("usage: edge can't exist in void");
	if (j == 0)
		ft_terminate("usage: edge can't exist in void");
	if (i == map_info->height - 1)
		ft_terminate("usage: edge can't exist in void");
	if (j == map_info->width - 1)
		ft_terminate("usage: edge can't exist in void");
}

void	check_surround_by_wall(t_map_info *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			if (map_info->map[i][j] == 2)
			{
				check_edge_is_empty(map_info, i, j);
				check_opened_wall(map_info, i, j);
			}
			if (map_info->map[i][j] == 3 || map_info->map[i][j] == 4
				|| map_info->map[i][j] == 5 || map_info->map[i][j] == 6)
				check_player_place_in_void(map_info, i, j);
			++j;
		}
		++i;
	}
}
