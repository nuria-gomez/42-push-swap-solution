/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 14:21:17 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 14:21:21 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_data *data)
{
	t_stack	*node_b;

	if (!data->stack_b)
		return ;
	node_b = data->stack_b;
	data->stack_b = data->stack_b->next;
	node_b->next = data->stack_a;
	data->stack_a = node_b;
	data->size_b--;
	data->size_a++;
	write(1, "pa\n", 3);
}

void	pb(t_data *data)
{
	t_stack	*node_a;

	if (!data->stack_a)
		return ;
	node_a = data->stack_a;
	data->stack_a = data->stack_a->next;
	node_a->next = data->stack_b;
	data->stack_b = node_a;
	data->size_a--;
	data->size_b++;
	write(1, "pb\n", 3);
}

void	ra(t_data *data, char instructions)
{
	t_stack	*top;
	t_stack	*last;

	if (!data->stack_a || !data->stack_a->next)
		return ;
	top = data->stack_a;
	data->stack_a = data->stack_a->next;
	top->next = NULL;
	last = data->stack_a;
	while (last->next)
		last = last->next;
	last->next = top;
	if (instructions != 'n')
		write(1, "ra\n", 3);
}

void	rb(t_data *data, char instructions)
{
	t_stack	*top;
	t_stack	*last;

	if (!data->stack_b || !data->stack_b->next)
		return ;
	top = data->stack_b;
	data->stack_b = data->stack_b->next;
	top->next = NULL;
	last = data->stack_b;
	while (last->next)
		last = last->next;
	last->next = top;
	if (instructions != 'n')
		write(1, "rb\n", 3);
}
