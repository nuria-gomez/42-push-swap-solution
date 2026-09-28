/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:53:03 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 13:53:05 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	binary_search(int *lis, int num, int size)
{
	int	max;
	int	med;
	int	min;

	max = size;
	med = 0;
	min = 0;
	while (min < max)
	{
		med = (max + min) / 2;
		if (num > lis[med])
			min = med + 1;
		else
			max = med;
	}
	return (min);
}

void	extract_lis(t_stack *stack_a, int *parents, int *pos_stack_a, int size)
{
	t_stack	*temp;
	int		i;
	int		j;

	i = pos_stack_a[size - 1];
	while (i != -1)
	{
		temp = stack_a;
		j = 0;
		while (j < i)
		{
			temp = temp->next;
			j++;
		}
		temp->in_lis = 1;
		i = parents[i];
	}
}

int	lis_len_calc(t_data *data)
{
	int	*act_lis;
	int	*pos_stack_a;
	int	*parents;
	int	lis_len;

	init_lis_arrays(data, &act_lis, &pos_stack_a, &parents);
	lis_len = build_lis(data, act_lis, pos_stack_a, parents);
	free(act_lis);
	free(pos_stack_a);
	free(parents);
	return (lis_len);
}

void	lis_calc(t_data *data)
{
	int	*act_lis;
	int	*pos_stack_a;
	int	*parents;
	int	lis_len;

	init_lis_arrays(data, &act_lis, &pos_stack_a, &parents);
	lis_len = build_lis(data, act_lis, pos_stack_a, parents);
	extract_lis(data->stack_a, parents, pos_stack_a, lis_len);
	free(act_lis);
	free(pos_stack_a);
	free(parents);
}
