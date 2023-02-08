/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_except_map_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:16:05 by junji             #+#    #+#             */
/*   Updated: 2023/02/08 17:03:31 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_terminate("usage: map file element allow (NO SO WE EA F A)");
}

static void	check_valid_word_count(char **splited)
{
	int		i;

	i = 0;
	while (splited[i])
		++i;
	if (i != 2)
		ft_terminate("map: invalid map");
}

static void	remove_newline(char *line)
{
	const int	len = ft_strlen(line);

	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static bool	skip_new_line(char *line)
{
	if (!ft_strcmp(line, "\n"))
	{
		free(line);
		return (true);
	}
	return (false);
}

void	read_except_map_content(int fd, t_map_info *map_info)
{
	char	*line;
	char	**splited;
	int		read_count;

	read_count = 0;
	while (1)
	{
		if (read_count == 6)
			break ;
		line = get_next_line(fd);
		if (!line)
			ft_terminate("map: invalid map");
		if (skip_new_line(line))
			continue ;
		remove_newline(line);
		splited = ft_split(line, ' ');
		check_valid_word_count(splited);
		check_type_identifier(splited);
		fill_except_map_content(map_info, splited);
		free_2d_array_content(splited);
		++read_count;
		free(line);
	}
}
