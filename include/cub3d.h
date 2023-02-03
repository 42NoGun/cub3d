/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:08 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 15:56:24 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480
# define TEX_WIDTH	64
# define TEX_HEIGHT	64
# define NO "./texture/bluestone.png"
# define SO "./texture/colorstone.png"
# define WE "./texture/eagle.png"
# define EA "./texture/greystone.png"

typedef struct s_image		t_image;
typedef struct s_map		t_map;
typedef struct s_texture	t_texture;
typedef struct s_color		t_color;
typedef struct s_player		t_player;

typedef enum e_key
{
	A = 0,
	S = 1,
	D = 2,
	W = 13,
	ESC = 53,
	LEFT = 123,
	RIGHT = 124,
	OPEN = 33,
	CLOSE = 30
}	t_key;

typedef struct s_image
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*display;
	void	*window;
	t_image	*image;
}	t_mlx;

typedef struct s_texture
{
	char	*relative_path;
	int		width;
	int		height;
	t_image	*image;
}	t_texture;

typedef struct s_color
{
	unsigned int	floor_color;
	unsigned int	ceilling_color;
}	t_color;

typedef struct s_map
{
	char	**world_map;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{	
	char	init_state;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_raycast
{
	double	ratio;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	walldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
}	t_raycast;

typedef struct s_data
{
	t_texture	*wall;
	t_color		*color;
	t_map		*map;
	t_player	*player;
	t_mlx		*mlx;
}	t_data;

typedef struct s_map_info
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		width;
	int		height;
}	t_map_info;



/*
 * parse.c
 */
void	parse(int argc, char *argv[], t_map_info *map_info);

/*
 * read_map_content.c
 */
void	read_map_content(int fd, t_map_info *map_info,
			t_list *map_line, bool is_first_new_line);

/*
 * read_except_map_content.c
 */
void	read_except_map_content(int fd, t_map_info *map_info);

/*
 * check_valid_map_element.c
 */
void	get_map_from_file(char *argv[], t_map_info *map_info, t_list *map_line);

/*
 * check_valid_map_element.c
 */
void	check_valid_map_element(t_list *map_line);

/*
 * create_map.c
 */
void	create_map(t_map_info *map_info, t_list *map_line);

/*
 * fill_empty_location.c
 */
void	fill_empty_location(t_map_info *map_info);

/*
 * check_surround_by_wall.c
 */
void	check_surround_by_wall(t_map_info *map_info);

/*
 * launch_game.c
 */
void	launch_game(t_map_info *map_info);

/*
 * free.c
 */
void	free_rest(t_data *data);
void	free_list_node_content(t_list *list);
void	free_2d_array_content(char **array);

/*
 * init_data.c
 */
t_data	*init_data(t_map_info *map_info, t_mlx *mlx);

/*
 * init_data_utils.c
 */
void	get_player_init_pos(t_player *player, t_map *map);
void	get_player_init_dir(t_player *player);
void	get_player_init_plane(t_player *player);

/*
 * init_mlx.c
 */
t_mlx	*init_mlx(void);

/*
 * render_wall_by_raycast.c
 */
void	render_wall_by_raycast(t_data *data);

/*
 * draw_wall_to_image.c
 */
void	draw_wall_to_image(t_data *data, t_raycast *cur_state, int x);


void	put_pixel_to_image(t_image *image, int x, int y, unsigned int color);
int		key_hook(int keycode, t_data *data);
void	exit_window(int keycode, t_data *data);
int		win_close(t_data *data);

#endif
