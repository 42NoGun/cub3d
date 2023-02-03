/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:22:53 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 13:21:25 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_newline(const char *backup)
{
	int	i;

	i = 0;
	if (!backup)
		return (-1);
	while (backup[i] != '\0')
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
