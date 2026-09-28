/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:53:35 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 11:33:02 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	clear_stacks(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

int	add_node(char *arr, t_stack **data_stack_a)
{
	t_stack	*tmp;
	t_stack	*stack_a;
	int		num;

	if (string_check(arr, *data_stack_a, &num))
		return (1);
	stack_a = malloc(sizeof(t_stack));
	if (!stack_a)
		return (1);
	stack_a->num = num;
	stack_a->next = NULL;
	stack_a->indx = 0;
	stack_a->in_lis = 0;
	if (!*data_stack_a)
		*data_stack_a = stack_a;
	else
	{
		tmp = *data_stack_a;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = stack_a;
	}
	return (0);
}

void	push_lis_to_b(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = data->size_a;
	while (i < size)
	{
		if (data->stack_a->in_lis == 1)
		{
			pb(data);
			rb(data, 'p');
		}
		else
			ra(data, 'p');
		i++;
	}
}

void	push_not_lis(t_data *data)
{
	int	i;
	int	size;
	int	median;

	i = 0;
	size = data->size_a;
	median = size / 2;
	while (i < size)
	{
		if (data->stack_a->in_lis == 0)
		{
			if (data->stack_a->indx < median)
			{
				pb(data);
				rb(data, 'p');
			}
			else
				pb(data);
		}
		else
			ra(data, 'p');
		i++;
	}
}
