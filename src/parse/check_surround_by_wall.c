/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surround_by_wall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:24:22 by junji             #+#    #+#             */
/*   Updated: 2023/02/08 15:39:37 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_surround(t_map_info *map_info, int i, int j, char *error_msg)
{
	const int	dy[] = {1, -1, 0, 0};
	const int	dx[] = {0, 0, 1, -1};
	int			dir;
	int			ny;
	int			nx;

	dir = -1;
	while (++dir < 4)
	{
		ny = i + dy[dir];
		nx = j + dx[dir];
		if (ny < 0 || nx < 0 || ny >= map_info->height || nx >= map_info->width)
			ft_terminate(error_msg);
		if (map_info->map[ny][nx] == -1)
			ft_terminate(error_msg);
	}
}

static void	check_edge_is_empty(t_map_info *map_info, int i, int j)
{
	if (i == 0)
		ft_terminate("usage: empty can't exist in edge");
	if (j == 0)
		ft_terminate("usage: empty can't exist in edge");
	if (i == map_info->height - 1)
		ft_terminate("usage: empty can't exist in edge");
	if (j == map_info->width - 1)
		ft_terminate("usage: empty can't exist in edge");
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
				check_surround(map_info, i, j,
					"usage: empty area must surrounded by walls");
			}
			if (map_info->map[i][j] == 3 || map_info->map[i][j] == 4
				|| map_info->map[i][j] == 5 || map_info->map[i][j] == 6)
				check_surround(map_info, i, j,
					"usage: player must located in walls");
			++j;
		}
		++i;
	}
}
