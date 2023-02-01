/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:43:27 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 09:45:03 by junji            ###   ########.fr       */
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
}

// void	check_valid_map(char *argv[])
// {

// }

void	fill_except_map_content(t_map_info *map_info, char **splited)
{
	if (ft_strcmp(splited[0], "NO"))
	{
		map_info->north_path = ft_strdup(splited[1]);
		printf("northda\n");
	}
	else if (ft_strcmp(splited[1], "NO"))
		map_info->north_path = ft_strdup(splited[0]);
	else if (ft_strcmp(splited[0], "SO"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (ft_strcmp(splited[1], "SO"))
		map_info->north_path = ft_strdup(splited[0]);
	else if (ft_strcmp(splited[0], "WE"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (ft_strcmp(splited[1], "WE"))
		map_info->north_path = ft_strdup(splited[0]);
	else if (ft_strcmp(splited[0], "EA"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (ft_strcmp(splited[1], "EA"))
		map_info->north_path = ft_strdup(splited[0]);
	else if (ft_strcmp(splited[0], "F"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (ft_strcmp(splited[1], "F"))
		map_info->north_path = ft_strdup(splited[0]);
	else if (ft_strcmp(splited[0], "C"))
		map_info->north_path = ft_strdup(splited[1]);
	else if (ft_strcmp(splited[1], "C"))
		map_info->north_path = ft_strdup(splited[0]);
}

void	check_type_identifier(char **splited)
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
	ft_putendl_fd("error\n", 2);
	exit(1);
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
		if (!line || !ft_strcmp(line, "\n"))
			continue ;
		splited = ft_split(line, ' ');
		check_type_identifier(splited);
		fill_except_map_content(map_info, splited);
		free_2d_array_content(splited);
		++read_count;
	}
	printf("north:%s\n", map_info->north_path);
	printf("south:%s\n", map_info->south_path);
	printf("east:%s\n", map_info->east_path);
	printf("west:%s\n", map_info->west_path);
}

void	read_map_content(int fd, t_map_info *map_info, t_list *map_line)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strcmp(line, ""))
			ft_terminate("error");
		++map_info->height;
		map_info->width = ft_strlen(line);
		if (line[map_info->width - 1] == '\n')
			line[map_info->width - 1] = 0;
		push_back(map_line, make_node(line));
	}
}

void	get_map_from_file(char *argv[], t_map_info *map_info)
{
	t_list	*map_line;
	int		fd;
	bool	first_new_line;

	first_new_line = false;
	map_line = init_list();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_terminate("open");
	read_except_map_content(fd, map_info);
	read_map_content(fd, map_info, map_line);
	t_node	*cur_node;

	cur_node = map_line->head;
	while (cur_node)
	{
		printf("%s\n", cur_node->content);
		cur_node = cur_node->next;
	}
	close(fd);
}

void	parse(int argc, char *argv[], t_map_info *map_info)
{
	ft_memset(map_info, 0, sizeof(t_map_info));
	check_valid_argument(argc, argv);
	get_map_from_file(argv, map_info);
	// check_valid_map(argv);
}
