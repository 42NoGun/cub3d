/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:11:28 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/08 16:59:45 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

void	ft_terminate(const char *str)
{
	const char	*err = strerror(errno);

	ft_putendl_fd("Error", 2);
	if (errno == 0)
		ft_putstr_fd((char *)str, 2);
	else
		ft_putstr_fd((char *)err, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
