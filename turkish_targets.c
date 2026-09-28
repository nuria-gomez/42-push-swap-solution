/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turkish_targets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:55:31 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:55:32 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min_node(t_stack *stack)
{
	t_stack	*current;
	t_stack	*min_node;

	if (!stack)
		return (NULL);
	current = stack;
	min_node = stack;
	current = current->next;
	while (current)
	{
		if (current->num < min_node->num)
			min_node = current;
		current = current->next;
	}
	return (min_node);
}

void	set_targets_b_to_a(t_data *data)
{
	t_stack	*current_a;
	t_stack	*current_b;
	t_stack	*target_node;
	long	best_match;

	current_b = data->stack_b;
	while (current_b)
	{
		best_match = LONG_MAX;
		current_a = data->stack_a;
		while (current_a)
		{
			if (current_a->num > current_b->num && current_a->num < best_match)
			{
				best_match = current_a->num;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_match == LONG_MAX)
			current_b->target = find_min_node(data->stack_a);
		else
			current_b->target = target_node;
		current_b = current_b->next;
	}
}

t_stack	*find_max_node(t_stack *stack)
{
	t_stack	*current;
	t_stack	*max_node;

	if (!stack)
		return (NULL);
	current = stack;
	max_node = stack;
	current = current->next;
	while (current)
	{
		if (current->num > max_node->num)
			max_node = current;
		current = current->next;
	}
	return (max_node);
}

void	set_targets_a_to_b(t_data *data)
{
	t_stack	*current_a;
	t_stack	*current_b;
	t_stack	*target_node;
	long	best_match;

	current_a = data->stack_a;
	while (current_a)
	{
		best_match = LONG_MIN;
		current_b = data->stack_b;
		while (current_b)
		{
			if (current_b->num < current_a->num && current_b->num > best_match)
			{
				best_match = current_b->num;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		if (best_match == LONG_MIN)
			current_a->target = find_max_node(data->stack_b);
		else
			current_a->target = target_node;
		current_a = current_a->next;
	}
}
