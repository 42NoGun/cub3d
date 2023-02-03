/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:43:27 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 14:03:24 by junji            ###   ########.fr       */
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
	ft_terminate("usage: map file element allow (NO SO WE EA F A)\n");
}

// 1. NO SO WE 만나오고 더 없었을 때 무한루프?
// 2. 공백을 기준으로 스플릿했을 때 splited2개가 없을 때
void	check_valid_word_count(char **splited)
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

int	skip_first_new_line(char *line, bool is_first_new_line)
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
				ft_terminate("error: map is empty");
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

void	fill_map(t_map_info *map_info, char	*line, int i)
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

void	init_map(t_map_info *map_info, t_list *map_line)
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
	for (int i = 0; i < map_info->height; i++)
	{
		for (int j = 0; j < map_info->width; j++)
		{
			printf("%d", map_info->map[i][j]);
		}
		printf("\n");
	}
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

bool	is_player_direction(char c)
{
	return (c == 'E' || c == 'W' || c == 'S' || c == 'N');
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
		ft_terminate("error: player is not exist\n");
}

void	search_adjacent_vertex(t_queue *queue, t_pair *cur,
	t_map_info *map_info)
{
	const int	dy[] = {-1, 1, 0, 0};
	const int	dx[] = {0, 0, 1, -1};
	int			dir;
	int			ny;
	int			nx;

	dir = -1;
	while (++dir < 4)
	{
		ny = cur->y + dy[dir];
		nx = cur->x + dx[dir];
		if (ny < 0 || ny >= map_info->height || nx < 0 || nx >= map_info->width)
			continue ;
		if (map_info->map[ny][nx] != 0)
			continue ;
		map_info->map[ny][nx] = 2;
		cur->y = ny;
		cur->x = nx;
		queue->push(queue, (void *)cur);
	}
}

void	bfs(t_queue *queue, t_map_info *map_info)
{
	t_pair		*cur;

	while (!queue->empty(queue))
	{
		cur = (t_pair *)(queue->front(queue));
		queue->pop(queue);
		search_adjacent_vertex(queue, cur, map_info);
	}
}

void	visit_empty_location(t_queue *queue, t_map_info *map_info, int i, int j)
{
	t_pair	*cur;

	cur = ft_calloc(sizeof(t_pair), 1);
	map_info->map[i][j] = 2;
	cur->y = i;
	cur->x = j;
	queue->push(queue, (void *)(cur));
}

void	fill_empty_location(t_map_info *map_info)
{
	int			i;
	int			j;
	t_queue		queue;

	i = 0;
	init_queue(&queue, sizeof(t_pair), map_info->height * map_info->width);
	while (i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			if (map_info->map[i][j] == 0)
				visit_empty_location(&queue, map_info, i, j);
			bfs(&queue, map_info);
			++j;
		}
		++i;
	}
}

void	check_edge_is_empty(t_map_info *map_info, int i, int j)
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

void	check_opened_wall(t_map_info *map_info, int i, int j)
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

void	check_player_place_in_void(t_map_info *map_info, int i, int j)
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

	int i, j;
	i = 0;
	while (i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			printf("%d", map_info->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}
