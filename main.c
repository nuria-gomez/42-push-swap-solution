/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:53:24 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 10:36:58 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.stack_a = NULL;
	data.stack_b = NULL;
	data.size_a = 0;
	data.size_b = 0;
	if (argc < 2)
		return (0);
	if (argc == 2)
		split_array_add_size(&data, argv[1]);
	if (argc > 2)
		parse_argv_add_size(&data, argv);
	if (normalize_init_checks(&data))
		lis_turkish_operations(&data);
	return (0);
}
