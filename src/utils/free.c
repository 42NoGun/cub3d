/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:32:11 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 16:57:26 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rest(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		free(data->wall[i].relative_path);
		//mlx_destroy_image(data->wall[i].image, data->mlx);
		free(data->wall[i].image);
		++i;
	}
	free(data->wall);
	free(data->color);
	free_2d_array_content(data->map->world_map);
	free(data->map);
	free(data->player);
}

void	free_list_node_content(t_list *list)
{
	t_node	*cur_node;
	t_node	*next_node;

	cur_node = list->head;
	while (cur_node)
	{
		next_node = cur_node->next;
		free(cur_node->content);
		free(cur_node);
		cur_node = next_node;
	}
	free(list);
}

void	free_2d_array_content(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}
