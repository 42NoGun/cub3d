/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array_map_from_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:16:49 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 11:01:02 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*read_mapfile(char **argv)
{
	t_queue	queue;
	t_list	*list;
	char	*line;	
	char	**rect;
	int		fd;
	int		height;
	int		width;
	int		max_width;
	int		i;
	int		j;
	t_node	*cur_node;

	list = init_list();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_terminate("open");
	height = 0;
	max_width = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		++height;
		width = ft_strlen(line);
		if (line[width - 1] == '\n')
			line[width - 1] = 0;
		if (max_width < width)
			max_width = width;
		printf("width: %d\n", width);
		printf("max_width: %d\n", max_width);
		push_back(list, make_node(line));
	}
	printf("height:%d\n", height);
	printf("max_width: %d\n", max_width);
	queue.data = ft_calloc(sizeof(t_pair), height * max_width);
	rect = ft_calloc(sizeof(char *), height);
	i = -1;
	while (++i < height)
		rect[i] = ft_calloc(sizeof(char), (max_width + 1));
	cur_node = list->head;
	i = 0;
	while (cur_node)
	{
	 	j = 0;
		while (((char *)(cur_node->content))[j])
		{
			if (((char *)(cur_node->content))[j] == ' ')
				rect[i][j] = -1;
			else if (((char *)(cur_node->content))[j] == 'E')	
				rect[i][j] = 3;
			else if (((char *)(cur_node->content))[j] == 'W')	
				rect[i][j] = 4;
			else if (((char *)(cur_node->content))[j] == 'S')	
				rect[i][j] = 5;
			else if (((char *)(cur_node->content))[j] == 'N')	
				rect[i][j] = 6;
			else
				rect[i][j] = ((char *)(cur_node->content))[j] - '0';
			printf("rect[%d][%d]:%d\n", i, j, rect[i][j]);
			++j;
		}
		while (j < width)
		{
			rect[i][j] = -1;
			++j;
		}
		++i;
		cur_node = cur_node->next;
	}
	printf("rect\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d", rect[i][j]);
		}
		printf("\n");
	}
	const int dy[] = {-1, 1, 0, 0};
	const int dx[] = {0, 0, 1, -1};
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rect[i][j] == 0)
			{
				t_pair cur;
				rect[i][j] = 2;
				cur.y = i;
				cur.x = j;
				queue.push(&queue, (void *)(&cur));
			}
			while (!queue.empty(&queue))
			{
				t_pair *cur;
				cur = (t_pair *)(queue.front(&queue));
				queue.pop(&queue);
				for (int i = 0; i < 4; ++i)
				{
					int ny = (*cur).y + dy[i];
					int nx = (*cur).x + dx[i];
					if (ny < 0 || ny >= height || nx < 0 || nx >= (int)width)
						continue;
					if (rect[ny][nx] != 0)
						continue;
					rect[ny][nx] = 2;
					(*cur).y = ny;
					(*cur).x = nx;
					queue.push(&queue, (void *)cur);
				}
			}
		}
	}
	printf("rect\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d", rect[i][j]);
		}
		printf("\n");
	}
	printf("rect\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d", rect[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rect[i][j] == 2)
			{
				if (i == 0)
				{
					printf("error1\n");
					exit(1);
				}
				else if (j == 0)
				{
					printf("error2\n");
					exit(1);
				}
				else if (i == height)
				{
					printf("error3\n");
					exit(1);
				}
				else if (j == width)
				{
					printf("error4\n");
					exit(1);
				}
				const int east = j + 1;
				const int west = j - 1;
				const int south = i + 1;
				const int north = i - 1;
				if (rect[i][east] == -1)
				{
					printf("error5\n");
					exit(1);
				}
				else if (rect[i][west] == -1)
				{
					printf("error6\n");
					exit(1);
				}
				else if (rect[south][j] == -1)
				{
					printf("i:%d, j:%d\n", i, j);
					printf("error7\n");
					exit(1);
				}
				else if (rect[north][j] == -1)
				{
					printf("i:%d, j:%d\n", i, j);
					printf("error8\n");
					exit(1);
				}
			}
			else if (rect[i][j] == 3 || rect[i][j] == 4 || rect[i][j] == 5 || rect[i][j] == 6)
			{
				const int east = j + 1;
				const int west = j - 1;
				const int south = i + 1;
				const int north = i - 1;
				if (rect[i][east] == -1)
				{
					printf("error5\n");
					exit(1);
				}
				else if (rect[i][west] == -1)
				{
					printf("error6\n");
					exit(1);
				}
				else if (rect[south][j] == -1)
				{
					printf("i:%d, j:%d\n", i, j);
					printf("error7\n");
					exit(1);
				}
				else if (rect[north][j] == -1)
				{
					printf("i:%d, j:%d\n", i, j);
					printf("error8\n");
					exit(1);
				}
			}
		}
		printf("\n");
	}

	printf("\n");
	return (list);
}

char	**get_array_map(t_list *list)
{
	char	**ret;
	t_node	*cur_node;
	int		i;

	ret = _malloc(sizeof(char *) * (list->len + 1));
	i = 0;
	cur_node = list->head;
	while (cur_node)
	{
		ret[i++] = ft_strdup(cur_node->content);
		cur_node = cur_node->next;
	}
	ret[i] = NULL;
	return (ret);
}
