/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two_to_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:54:35 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:54:36 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_stack	*temp;
	int		previous;

	previous = 0;
	temp = stack;
	while (temp)
	{
		if (temp->indx != previous)
			return (0);
		temp = temp->next;
		previous++;
	}
	return (1);
}

void	sort_three(t_data *data)
{
	int	first;
	int	second;
	int	third;

	first = data->stack_a->indx;
	second = data->stack_a->next->indx;
	third = data->stack_a->next->next->indx;
	if (first > second && first > third)
		ra(data, 'p');
	else if (second > first && second > third)
		rra(data, 'p');
	if (data->stack_a->indx > data->stack_a->next->indx)
		sa(data);
}

void	sort_two_to_five(t_data *data)
{
	if (!data || !data->stack_a || data->size_a < 2)
		return ;
	if (data->size_a == 2)
	{
		if (data->stack_a->indx > data->stack_a->next->indx)
			sa(data);
		return ;
	}
	while (data->size_a > 3)
	{
		rotate_to_top_a(data, find_min_node(data->stack_a));
		pb(data);
	}
	sort_three(data);
	while (data->size_b > 0)
		pa(data);
}
