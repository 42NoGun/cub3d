/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:52:33 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 15:44:42 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*init_texture(t_map_info *map_info, t_mlx *mlx)
{
	t_texture	*wall;
	int			i;

	wall = _malloc(sizeof(t_texture) * 4);
	(wall[0]).relative_path = map_info->north_path;
	(wall[1]).relative_path = map_info->south_path;
	(wall[2]).relative_path = map_info->west_path;
	(wall[3]).relative_path = map_info->east_path;
	i = 0;
	while (i < 4)
	{
		wall[i].image = _malloc(sizeof(t_image));
		wall[i].image->img = mlx_png_file_to_image(mlx->display,
				wall[i].relative_path, &wall[i].width, &wall[i].height);
		if (wall[i].image->img == NULL)
			ft_terminate("");
		wall[i].image->addr = mlx_get_data_addr(wall[i].image->img,
				&wall[i].image->bits_per_pixel,
				&wall[i].image->size_line, &wall[i].image->endian);
		++i;
	}
	return (wall);
}

static t_color	*init_color(t_map_info *map_info)
{
	t_color	*color;

	color = _malloc(sizeof(t_color));
	color->floor_color = map_info->floor_color;
	color->ceilling_color = map_info->ceiling_color;
	return (color);
}

static t_map	*init_map(t_map_info *map_info)
{
	t_map	*map;

	map = _malloc(sizeof(t_map));
	map->world_map = map_info->map;
	map->height = map_info->height;
	map->width = map_info->width;
	return (map);
}

static t_player	*init_player(t_map *map)
{
	t_player	*player;

	player = _malloc(sizeof(t_player));
	get_player_init_pos(player, map);
	get_player_init_dir(player);
	get_player_init_plane(player);
	return (player);
}

t_data	*init_data(t_map_info *map_info, t_mlx *mlx)
{
	t_data	*data;

	data = _malloc(sizeof(t_data));
	data->wall = init_texture(map_info, mlx);
	data->color = init_color(map_info);
	data->map = init_map(map_info);
	data->player = init_player(data->map);
	data->mlx = mlx;
	return (data);
}
