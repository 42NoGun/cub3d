/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:20:20 by junji             #+#    #+#             */
/*   Updated: 2023/02/08 17:02:05 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map(t_map_info *map_info, char	*line, int i)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == ' ')
			map_info->map[i][j] = -1;
		else if (line[j] == 'E')
			map_info->map[i][j] = 3;
		else if (line[j] == 'W')
			map_info->map[i][j] = 4;
		else if (line[j] == 'S')
			map_info->map[i][j] = 5;
		else if (line[j] == 'N')
			map_info->map[i][j] = 6;
		else
			map_info->map[i][j] = line[j] - '0';
		++j;
	}
	while (j < map_info->width)
	{
		map_info->map[i][j] = -1;
		++j;
	}
}

static void	init_map(t_map_info *map_info, t_list *map_line)
{
	int		i;
	t_node	*cur_node;
	char	*line;

	cur_node = map_line->head;
	i = 0;
	while (cur_node)
	{
		line = (char *)(cur_node->content);
		fill_map(map_info, line, i);
		++i;
		cur_node = cur_node->next;
	}
}

void	create_map(t_map_info *map_info, t_list *map_line)
{
	int		i;

	map_info->map = ft_calloc(sizeof(char *), map_info->height + 1);
	i = -1;
	while (++i < map_info->height)
		map_info->map[i] = ft_calloc(sizeof(char), map_info->width + 1);
	init_map(map_info, map_line);
}
