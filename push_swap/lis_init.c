/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 14:15:52 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 10:49:40 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_lis_arrays(t_data *data, int **act_lis,
		int **pos_stack_a, int **parents)
{
	*act_lis = malloc(data->size_a * sizeof(int));
	if (!*act_lis)
		ft_error_data(data);
	*pos_stack_a = malloc(data->size_a * sizeof(int));
	if (!*pos_stack_a)
	{
		free(*act_lis);
		ft_error_data(data);
	}
	*parents = malloc(data->size_a * sizeof(int));
	if (!*parents)
	{
		free(*act_lis);
		free(*pos_stack_a);
		ft_error_data(data);
	}
}

int	build_lis(t_data *data, int *act_lis,
		int *pos_stack_a, int *parents)
{
	t_stack	*temp;
	int		i;
	int		index_in_lis;
	int		lis_len;

	temp = data->stack_a;
	i = 0;
	lis_len = 0;
	while (temp)
	{
		index_in_lis = binary_search(act_lis, temp->indx, lis_len);
		if (index_in_lis == 0)
			parents[i] = -1;
		else
			parents[i] = pos_stack_a[index_in_lis - 1];
		pos_stack_a[index_in_lis] = i;
		act_lis[index_in_lis] = temp->indx;
		if (index_in_lis == lis_len)
			lis_len++;
		temp = temp->next;
		i++;
	}
	return (lis_len);
}

int	build_inverted_lis(t_data *data, int *act_lis,
		int *pos_lis, int *parents)
{
	t_stack	*temp;
	int		i;
	int		index_in_lis;
	int		lis_len;

	temp = data->stack_a;
	i = 0;
	lis_len = 0;
	while (temp)
	{
		index_in_lis = inverted_binary_search(act_lis, temp->indx, lis_len);
		if (index_in_lis == 0)
			parents[i] = -1;
		else
			parents[i] = pos_lis[index_in_lis - 1];
		pos_lis[index_in_lis] = i;
		act_lis[index_in_lis] = temp->indx;
		if (index_in_lis == lis_len)
			lis_len++;
		temp = temp->next;
		i++;
	}
	return (lis_len);
}
