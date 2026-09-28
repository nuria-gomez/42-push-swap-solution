/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turkish.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:55:42 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 10:42:41 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_sorted_to_a(t_data *data)
{
	while (data->size_b > 0)
		pa(data);
}

void	turkish_to_b(t_data *data)
{
	while (data->size_a > 0)
	{
		set_targets_a_to_b(data);
		calculate_costs_and_push(data, 2);
	}
	rotate_to_top_b(data, find_max_node(data->stack_b));
	push_sorted_to_a(data);
}

void	turkish_to_a(t_data *data)
{
	while (data->size_b > 0)
	{
		set_targets_b_to_a(data);
		calculate_costs_and_push(data, 1);
	}
	rotate_to_top_a(data, find_min_node(data->stack_a));
}

int	lis_turkish_operations(t_data *data)
{
	data->size_lis = lis_len_calc(data);
	data->size_inv_lis = inverted_lis_len_calc(data);
	if (data->size_inv_lis > data->size_lis
		&& data->size_inv_lis * 4 >= data->size_a * 3)
	{
		inverted_lis_calc(data);
		push_lis_to_b(data);
		if (data->size_a > 0)
			turkish_to_b(data);
		else
			push_sorted_to_a(data);
	}
	else
	{
		lis_calc(data);
		push_not_lis(data);
		turkish_to_a(data);
	}
	clear_stacks(&data->stack_a);
	clear_stacks(&data->stack_b);
	return (0);
}