/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_except_map_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:34:46 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/08 17:02:17 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_colors(int *fill_color, char *splited)
{
	char	**numbers;
	int		i;	
	int		color;

	numbers = ft_split(splited, ',');
	i = 0;
	while (numbers[i])
		++i;
	if (i != 3)
		ft_terminate("usage: color is three argument");
	i = -1;
	while (++i < 3)
	{
		*fill_color <<= 8;
		color = ft_atoi(numbers[i]);
		if (color < 0 || color > 255)
			ft_terminate("usage: ceiling color range is 0 ~ 255");
		*fill_color += color;
	}
	free_2d_array_content(numbers);
}

void	fill_except_map_content(t_map_info *map_info, char **splited)
{
	if (!ft_strcmp(splited[0], "NO"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (!ft_strcmp(splited[0], "SO"))
		map_info->south_path = ft_strdup(splited[1]);
	else if (!ft_strcmp(splited[0], "WE"))
		map_info->west_path = ft_strdup(splited[1]);
	else if (!ft_strcmp(splited[0], "EA"))
		map_info->east_path = ft_strdup(splited[1]);
	else if (!ft_strcmp(splited[0], "F"))
		fill_colors(&map_info->floor_color, splited[1]);
	else if (!ft_strcmp(splited[0], "C"))
		fill_colors(&map_info->ceiling_color, splited[1]);
}
