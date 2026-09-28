/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:53:46 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 10:50:06 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*data_copy(int size, t_stack *data_stack_a)
{
	int	i;
	int	*sorted;

	i = 0;
	sorted = malloc(size * sizeof(int));
	if (!sorted)
		return (NULL);
	while (data_stack_a)
	{
		sorted[i] = data_stack_a->num;
		data_stack_a = data_stack_a->next;
		i++;
	}
	return (sorted);
}

static int	*bubble_sort(int size, t_stack *data_stack_a)
{
	int	*sorted;
	int	j;
	int	i;
	int	temp;

	sorted = data_copy(size, data_stack_a);
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (sorted[j] > sorted[j + 1])
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

void	normalize_nodes(t_data *data)
{
	int		*sorted;
	int		i;
	t_stack	*tmp;

	tmp = data->stack_a;
	sorted = bubble_sort(data->size_a, data->stack_a);
	if (!sorted)
	{
		ft_error_data(data);
	}
	while (tmp)
	{
		i = 0;
		while (i < data->size_a)
		{
			if (sorted[i] == tmp->num)
			{
				tmp->indx = i;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	free(sorted);
}
