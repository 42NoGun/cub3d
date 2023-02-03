/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_except_map_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:16:05 by junji             #+#    #+#             */
/*   Updated: 2023/02/03 14:34:35 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_colors(int *fill_color, char *splited)
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
}

static void	fill_except_map_content(t_map_info *map_info, char **splited)
{
	splited[1][ft_strlen(splited[1]) - 1] = 0;
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

static void	check_type_identifier(char **splited)
{
	if (!ft_strcmp(splited[0], "NO") || !ft_strcmp(splited[1], "NO"))
		return ;
	if (!ft_strcmp(splited[0], "SO") || !ft_strcmp(splited[1], "SO"))
		return ;
	if (!ft_strcmp(splited[0], "WE") || !ft_strcmp(splited[1], "WE"))
		return ;
	if (!ft_strcmp(splited[0], "EA") || !ft_strcmp(splited[1], "EA"))
		return ;
	if (!ft_strcmp(splited[0], "F") || !ft_strcmp(splited[1], "F"))
		return ;
	if (!ft_strcmp(splited[0], "C") || !ft_strcmp(splited[1], "C"))
		return ;
	ft_terminate("usage: map file element allow (NO SO WE EA F A)\n");
}

static void	check_valid_word_count(char **splited)
{
	int		i;

	i = 0;
	while (splited[i])
		++i;
	if (i != 2)
		ft_terminate("error: type element must have 2 words\n");
}

void	read_except_map_content(int fd, t_map_info *map_info)
{
	char	*line;
	char	**splited;
	int		read_count;

	read_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (read_count == 6)
			break ;
		if (!line)
			ft_terminate("error: invalid map\n");
		if (!ft_strcmp(line, "\n"))
			continue ;
		splited = ft_split(line, ' ');
		check_valid_word_count(splited);
		check_type_identifier(splited);
		fill_except_map_content(map_info, splited);
		free_2d_array_content(splited);
		++read_count;
	}
	printf("north:%s\n", map_info->north_path);
	printf("south:%s\n", map_info->south_path);
	printf("east:%s\n", map_info->east_path);
	printf("west:%s\n", map_info->west_path);
	printf("ceiling:%x\n", map_info->ceiling_color);
	printf("floor:%x\n", map_info->floor_color);
}
