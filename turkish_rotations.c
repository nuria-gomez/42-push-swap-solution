/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turkish_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:55:16 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:55:17 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotates_up(int pos, int size)
{
	return (pos <= size / 2);
}

int	get_position(t_stack *stack, t_stack *node)
{
	int	index;

	index = 0;
	while (stack)
	{
		if (stack == node)
			return (index);
		stack = stack->next;
		index++;
	}
	return (-1);
}

void	rotate_to_top_a(t_data *data, t_stack *node)
{
	int	pos;

	pos = get_position(data->stack_a, node);
	if (pos < 0)
		return ;
	if (pos <= data->size_a / 2)
	{
		while (pos--)
			ra(data, 'p');
	}
	else
	{
		pos = data->size_a - pos;
		while (pos--)
			rra(data, 'p');
	}
}

void	rotate_to_top_b(t_data *data, t_stack *node)
{
	int	pos;

	pos = get_position(data->stack_b, node);
	if (pos < 0)
		return ;
	if (pos <= data->size_b / 2)
	{
		while (pos--)
			rb(data, 'p');
	}
	else
	{
		pos = data->size_b - pos;
		while (pos--)
			rrb(data, 'p');
	}
}
