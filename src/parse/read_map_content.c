/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:43:27 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/08 16:59:43 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	skip_first_new_line(char *line, bool is_first_new_line)
{
	if (!ft_strcmp(line, "\n"))
	{
		if (is_first_new_line)
		{
			free(line);
			return (1);
		}
		ft_terminate("usage: map content allowed newline only first line");
	}
	return (0);
}

void	read_map_content(int fd, t_map_info *map_info,
		t_list *map_line, bool is_first_new_line)
{
	char	*line;
	int		width;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (is_first_new_line)
				ft_terminate("map: map is empty");
			break ;
		}
		if (skip_first_new_line(line, is_first_new_line))
			continue ;
		++map_info->height;
		width = ft_strlen(line);
		if (line[width - 1] == '\n')
			line[width - 1] = 0;
		if (map_info->width < width - 1)
			map_info->width = width - 1;
		push_back(map_line, make_node(line));
		is_first_new_line = false;
	}
	close(fd);
}
