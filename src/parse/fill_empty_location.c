/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_empty_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:21:50 by junji             #+#    #+#             */
/*   Updated: 2023/02/03 16:48:25 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	search_adjacent_vertex(t_queue *queue, t_pair *cur,
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

static void	bfs(t_queue *queue, t_map_info *map_info)
{
	t_pair		*cur;

	while (!queue->empty(queue))
	{
		cur = (t_pair *)(queue->front(queue));
		queue->pop(queue);
		search_adjacent_vertex(queue, cur, map_info);
	}
}

static void	visit_empty_location(t_queue *queue, t_map_info *map_info,
		int i, int j)
{
	t_pair	cur;

	map_info->map[i][j] = 2;
	cur.y = i;
	cur.x = j;
	queue->push(queue, (void *)(&cur));
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
	free(queue.data);
}
