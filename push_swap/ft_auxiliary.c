/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxiliary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:52:35 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 11:02:18 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_size(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

static int	dup_check(long num, t_stack *stacka)
{
	while (stacka)
	{
		if (num == stacka->num)
			return(1);
		stacka = stacka->next;
	}
	return (0);
}

static int	string_check_ifs(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (-1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (-1);
	if (str[i] == '0' && str[i + 1] != '\0')
		return (-1);
	return (i);
}

int	string_check(char *str, t_stack *stack, int *outp)
{
	int		i;
	long	num;
	int		range;

	i = string_check_ifs(str);
	if ( i < 0)
		return(1);
	range = 0;
	while (str[i])
	{
		range++;
		if (str[i] < '0' || str[i] > '9' || range >= 11)
			return(1);
		i++;
	}
	num = ft_atol(str);
	if (num > INT_MAX || num < INT_MIN || dup_check(num, stack))
		return (1);
	*outp = (int)num;
	return (0);
}
