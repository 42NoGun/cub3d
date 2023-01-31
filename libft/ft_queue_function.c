/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:03:37 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 16:15:31 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	push(t_queue *queue, void *value)
{
	((t_pair *)(queue->data))[queue->tail].y = ((t_pair *)(value))->y;
	((t_pair *)(queue->data))[queue->tail].x = ((t_pair *)(value))->x;
}

void	pop(t_queue	*queue)
{
	++(queue->head);
}

bool	empty(t_queue *queue)
{
	const int	size = (queue->tail - queue->head);

	if (size == 0)
		return (true);
	return (false);
}

void	*front(t_queue *queue)
{
	return (&((queue->data)[queue->head]));
}

void	init_queue(t_queue *queue)
{
	queue->head = 0;
	queue->tail = 0;
	queue->push = push;
	queue->pop = pop;
	queue->empty = empty;
	queue->front = front;
}