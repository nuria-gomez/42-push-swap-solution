/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turkish_costs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:54:47 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:54:49 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*the_cheaper(t_stack *self)
{
	t_stack	*temp;
	t_stack	*winner_self;
	int		current_mov;
	int		best_mov;

	winner_self = self;
	temp = self;
	best_mov = temp->cost + temp->target->cost;
	while (temp)
	{
		current_mov = temp->cost + temp->target->cost;
		if (current_mov < best_mov)
		{
			best_mov = current_mov;
			winner_self = temp;
		}
		temp = temp->next;
	}
	return (winner_self);
}

void	calc_move_top_costs(t_stack *stacki, int size_stack)
{
	t_stack	*temp;
	int		counter;

	temp = stacki;
	counter = 0;
	while (temp)
	{
		if (counter <= (size_stack + 1) / 2)
			temp->cost = counter;
		else
			temp->cost = size_stack - counter;
		counter++;
		temp = temp->next;
	}
}

void	calculate_costs_and_push(t_data *data, int orientation)
{
	t_stack	*cheaper;

	calc_move_top_costs(data->stack_b, data->size_b);
	calc_move_top_costs(data->stack_a, data->size_a);
	if (orientation == 1)
		cheaper = the_cheaper(data->stack_b);
	else
		cheaper = the_cheaper(data->stack_a);
	push_cheaper(data, cheaper, orientation);
}
