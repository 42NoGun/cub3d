/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map_element.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:17:05 by junji             #+#    #+#             */
/*   Updated: 2023/02/08 17:20:45 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_duplicate_player(char c, int *dir_flag)
{
	if (*dir_flag & 0b1111)
		ft_terminate("usage: only one player can exist");
	if (c == 'E')
		*dir_flag |= 0b1000;
	if (c == 'W')
		*dir_flag |= 0b0100;
	if (c == 'S')
		*dir_flag |= 0b0010;
	if (c == 'N')
		*dir_flag |= 0b0001;
}

static bool	is_player_direction(char c)
{
	return (c == 'E' || c == 'W' || c == 'S' || c == 'N');
}

void	check_valid_map_element(t_list *map_line)
{
	t_node	*cur_node;
	char	*line;
	int		i;
	int		line_len;
	int		dir_flag;

	dir_flag = 0;
	cur_node = map_line->head;
	while (cur_node)
	{
		line = (char *)(cur_node->content);
		line_len = ft_strlen(line);
		i = -1;
		while (++i < line_len)
		{
			if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1'
					|| is_player_direction(line[i])))
				ft_terminate("usage: map only allowed (' ' 0 1 E W S N)");
			if (is_player_direction(line[i]))
				check_duplicate_player(line[i], &dir_flag);
		}
		cur_node = cur_node->next;
	}
	if (!dir_flag)
		ft_terminate("error: player is not exist");
}
