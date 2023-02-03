/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:03:37 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/02/03 13:21:56 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_queue(t_queue *queue, int count, int size)
{
	queue->head = 0;
	queue->tail = 0;
	queue->push = push;
	queue->pop = pop;
	queue->empty = empty;
	queue->front = front;
	queue->data = ft_calloc(count, size);
}

void	push(t_queue *queue, void *value)
{
	((t_pair *)(queue->data))[queue->tail].y = ((t_pair *)(value))->y;
	((t_pair *)(queue->data))[queue->tail].x = ((t_pair *)(value))->x;
}

void	pop(t_queue	*queue)
{
	if (queue->empty(queue))
		return ;
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
