/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:43:27 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/01 09:28:07 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse(int argc, char *argv[], t_map_info *map_info);

int	main(int argc, char **argv)
{
	t_map_info	map_info;
//	t_list		*list;
//	t_mlx		*mlx;
//	t_data		*data;

	parse(argc, argv, &map_info);
	// launch_game();

//	if (argc != 2)
//	{
//		ft_putendl_fd("Error: argnum\n", 2);
//		return (1);
//	}
//	list = read_mapfile(argv);
//	mlx = init_mlx();
//	data = init_data(list, mlx);
//	launch_game(data);
//	free_list_node_content(list);
	// system("leaks cub3D");
	return (0);
}
