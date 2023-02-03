# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 09:21:03 by jiyunpar          #+#    #+#              #
#    Updated: 2023/02/03 15:57:19 by hanbkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME				:=	cub3D

INIT				:=	init_data init_data_utils init_mlx
INIT_M				:=	$(addprefix src/init/, $(addsuffix .c, $(INIT)))

LAUNCH_GAME			:=	launch_game render_wall_by_raycast draw_wall_to_image key_hook_1 key_hook_2
LAUNCH_GAME_M		:=	$(addprefix src/launch_game/, $(addsuffix .c, $(LAUNCH_GAME)))

PARSE			:=	parse read_except_map_content read_map_content check_valid_map_element create_map fill_empty_location check_surround_by_wall
PARSE_M			:=	$(addprefix src/parse/, $(addsuffix .c, $(PARSE)))

UTILS				:=	free put_pixel_to_image
UTILS_M				:=	$(addprefix src/utils/, $(addsuffix .c, $(UTILS)))

MAIN				:=	main
MAIN_M				:=	$(addprefix src/, $(addsuffix .c, $(MAIN)))

SRCS				:=	$(PARSE_M) $(UTILS_M) $(MAIN_M) $(INIT_M) $(LAUNCH_GAME_M)

OBJS				:=	$(SRCS:.c=.o)

LIBFT_DIR			=	./libft

MLX_DIR				=	./mlx/

LIB_DIR				=	-L$(LIBFT_DIR) -L$(MLX_DIR)
LIB					= 	-lft -lmlx

INCLUDE				=	-I./include -I$(MLX_DIR) -I$(LIBFT_DIR)

CFLAGS				=	-Wall -Wextra -Werror -g3

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all	: .all_check

debugs	:
	make DEBUG=2

debug	:
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3
endif
ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address
endif

.all_check	: $(OBJS)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR) re
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB_DIR) $(LIB) \
			-framework OpenGL -framework AppKit -o $(NAME) $^
	$(CC) $(CFLAGS) $(LIB_DIR) $(LIB) -o $(NAME) $^
	install_name_tool -change libmlx.dylib @executable_path/${MLX_DIR}/libmlx.dylib ${NAME}
	touch $@

clean	:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean	:
	@make clean
	@rm -f .all_check
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re :
	@make fclean
	@make all
