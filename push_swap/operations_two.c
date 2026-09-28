/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 14:21:28 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 14:21:29 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_data *data, char instructions)
{
	t_stack	*last;
	t_stack	*before_last;

	if (!data->stack_a || !data->stack_a->next)
		return ;
	before_last = data->stack_a;
	while (before_last->next->next)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	last->next = data->stack_a;
	data->stack_a = last;
	if (instructions != 'n')
		write(1, "rra\n", 4);
}

void	rrb(t_data *data, char instructions)
{
	t_stack	*last;
	t_stack	*before_last;

	if (!data->stack_b || !data->stack_b->next)
		return ;
	before_last = data->stack_b;
	while (before_last->next->next)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	last->next = data->stack_b;
	data->stack_b = last;
	if (instructions != 'n')
		write(1, "rrb\n", 4);
}

void	rr(t_data *data)
{
	ra(data, 'n');
	rb(data, 'n');
	write(1, "rr\n", 3);
}

void	rrr(t_data *data)
{
	rra(data, 'n');
	rrb(data, 'n');
	write(1, "rrr\n", 4);
}

void	sa(t_data *data)
{
	t_stack	*first;
	t_stack	*second;

	if (!data->stack_a || !data->stack_a->next)
		return ;
	first = data->stack_a;
	second = first->next;
	first->next = second->next;
	second->next = first;
	data->stack_a = second;
	write(1, "sa\n", 3);
}
