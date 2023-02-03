/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:49:47 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 15:43:13 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_image *image, int x, int y, unsigned int color)
{
	char	*ret;

	ret = image->addr
		+ (y * image->size_line + x * (image->bits_per_pixel / 8));
	*((unsigned int *)ret) = color;
}
