/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:53:17 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 10:57:46 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	split_array_add_size(t_data *data, char *str)
{
	char	**arr;
	int		i;

	arr = NULL;
	arr = ft_split(str, 32);
	if (!arr || !arr[0])
	{
		free_darr(arr);
		ft_error_data(data);
	}
	i = 0;
	while (arr[i])
	{
		if (add_node(arr[i], &data->stack_a))
		{
			free_darr(arr);
			ft_error_data(data);
		}
		i++;
	}
	free_darr(arr);
	data->size_a = count_size(data->stack_a);
}

void	parse_argv_add_size(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (add_node(argv[i], &data->stack_a))
			ft_error_data(data);
		i++;
	}
	data->size_a = count_size(data->stack_a);
}

int	normalize_init_checks(t_data *data)
{
	normalize_nodes(data);
	if (is_sorted(data->stack_a))
	{
		clear_stacks(&data->stack_a);
		clear_stacks(&data->stack_b);
		return (0);
	}
	if (data->size_a <= 5)
	{
		sort_two_to_five(data);
		clear_stacks(&data->stack_a);
		clear_stacks(&data->stack_b);
		return (0);
	}
	return (1);
}
