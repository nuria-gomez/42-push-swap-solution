/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_inverted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:52:48 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/01 15:16:14 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	inverted_binary_search(int *lis, int num, int size)
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
		if (num < lis[med])
			min = med + 1;
		else
			max = med;
	}
	return (min);
}

void	extract_inverted_lis(t_stack *stack_a,
	int *parents, int *pos_lis, int size)
{
	t_stack	*temp;
	int		i;
	int		j;

	i = pos_lis[size - 1];
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

int	inverted_lis_len_calc(t_data *data)
{
	int	*act_lis;
	int	*pos_lis;
	int	*parents;
	int	lis_len;

	init_lis_arrays(data, &act_lis, &pos_lis, &parents);
	lis_len = build_inverted_lis(data, act_lis, pos_lis, parents);
	free(act_lis);
	free(pos_lis);
	free(parents);
	return (lis_len);
}

void	inverted_lis_calc(t_data *data)
{
	int	*act_lis;
	int	*pos_lis;
	int	*parents;
	int	lis_len;

	init_lis_arrays(data, &act_lis, &pos_lis, &parents);
	lis_len = build_inverted_lis(data, act_lis, pos_lis, parents);
	extract_inverted_lis(data->stack_a, parents, pos_lis, lis_len);
	free(act_lis);
	free(pos_lis);
	free(parents);
}
