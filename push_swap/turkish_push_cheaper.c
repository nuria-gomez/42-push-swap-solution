/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turkish_push_cheaper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:55:01 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:55:04 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	check_positions(t_data *data, t_stack *cheaper,
	int orientation, int *up)
{
	int	pos_self;
	int	pos_target;

	if (orientation == 1)
	{
		pos_self = get_position(data->stack_b, cheaper);
		pos_target = get_position(data->stack_a, cheaper->target);
		up[0] = rotates_up(pos_self, data->size_b);
		up[1] = rotates_up(pos_target, data->size_a);
	}
	else
	{
		pos_self = get_position(data->stack_a, cheaper);
		pos_target = get_position(data->stack_b, cheaper->target);
		up[0] = rotates_up(pos_self, data->size_a);
		up[1] = rotates_up(pos_target, data->size_b);
	}
}

void	check_move_rr(t_data *data, t_stack *cheaper, int orientation)
{
	int	up[2];
	int	common;

	check_positions(data, cheaper, orientation, up);
	if (up[0] != up[1])
		return ;
	common = cheaper->cost;
	if (cheaper->target->cost < common)
		common = cheaper->target->cost;
	while (common--)
	{
		if (up[0])
			rr(data);
		else
			rrr(data);
	}
}

void	push_cheaper(t_data *data, t_stack *cheaper, int orientation)
{
	check_move_rr(data, cheaper, orientation);
	if (orientation == 1)
	{
		rotate_to_top_b(data, cheaper);
		rotate_to_top_a(data, cheaper->target);
		pa(data);
	}
	else
	{
		rotate_to_top_a(data, cheaper);
		rotate_to_top_b(data, cheaper->target);
		pb(data);
	}
}
