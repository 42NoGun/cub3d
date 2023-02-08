/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:43:27 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/08 17:03:21 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_valid_argument(int argc, char *argv[])
{
	char	**file_extension;
	int		i;

	if (argc != 2)
	{
		ft_putendl_fd("usage: ./cub3d mapfile", 2);
		exit(1);
	}
	file_extension = ft_split(argv[1], '.');
	i = 0;
	while (file_extension[i])
		++i;
	if (!file_extension[i - 1] || ft_strcmp(file_extension[i - 1], "cub"))
	{
		ft_putendl_fd("usage: mapfile is [mapname.cub]", 2);
		exit(1);
	}
	free_2d_array_content(file_extension);
}

void	check_duplicate_player(char c, int *dir_flag)
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

void	get_map_from_file(char *argv[], t_map_info *map_info, t_list *map_line)
{
	int		fd;
	bool	first_new_line;

	first_new_line = false;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_terminate("open");
	read_except_map_content(fd, map_info);
	read_map_content(fd, map_info, map_line, true);
}

void	parse(int argc, char *argv[], t_map_info *map_info)
{
	t_list	*map_line;

	errno = 0;
	map_line = init_list();
	ft_memset(map_info, 0, sizeof(t_map_info));
	check_valid_argument(argc, argv);
	get_map_from_file(argv, map_info, map_line);
	check_valid_map_element(map_line);
	create_map(map_info, map_line);
	fill_empty_location(map_info);
	check_surround_by_wall(map_info);
	free_list_node_content(map_line);
}
