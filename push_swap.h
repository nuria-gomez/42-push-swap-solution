/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 13:54:22 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 11:33:04 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>

# include <stdlib.h>

# include <limits.h>

typedef struct s_stack
{
	int				num;
	int				indx;
	int				in_lis;
	int				cost;
	struct s_stack	*target;
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size_a;
	int		size_b;
	int		size_lis;
	int		size_inv_lis;
}	t_data;

int		ft_error_data(t_data *data);
void	split_array_add_size(t_data *data, char *str);
void	parse_argv_add_size(t_data *data, char **argv);
int		normalize_init_checks(t_data *data);
int		lis_turkish_operations(t_data *data);
long	ft_atol(const char *nptr);
char	**ft_split(char const *s, char c);
int		ft_error(int error_code);
int		count_size(t_stack *stack);
int		string_check(char *str, t_stack *stack, int *outp);
void	free_darr(char **arr);
void	clear_stacks(t_stack **stack);
int		add_node(char *arr, t_stack **data_stack_a);
void	push_not_lis(t_data *data);
void	push_lis_to_b(t_data *data);
void	normalize_nodes(t_data *data);
int		*data_copy(int size, t_stack *data_stack_a);
void	init_lis_arrays(t_data *data, int **act_lis,
			int **pos_stack_a, int **parents);
int		lis_len_calc(t_data *data);
void	lis_calc(t_data *data);
int		inverted_lis_len_calc(t_data *data);
void	inverted_lis_calc(t_data *data);
int		inverted_binary_search(int *lis, int num, int size);
int		binary_search(int *lis, int num, int size);
int		build_inverted_lis(t_data *data, int *act_lis,
			int *pos_lis, int *parents);
int		build_lis(t_data *data, int *act_lis,
			int *pos_stack_a, int *parents);
void	pb(t_data *data);
void	pa(t_data *data);
void	ra(t_data *data, char instructions);
void	rb(t_data *data, char instructions);
void	rra(t_data *data, char instructions);
void	rrb(t_data *data, char instructions);
void	rr(t_data *data);
void	rrr(t_data *data);
void	turkish_to_a(t_data *data);
void	turkish_to_b(t_data *data);
void	push_sorted_to_a(t_data *data);
void	set_targets_b_to_a(t_data *data);
void	set_targets_a_to_b(t_data *data);
t_stack	*find_min_node(t_stack *stack);
t_stack	*find_max_node(t_stack *stack);
void	calculate_costs_and_push(t_data *data, int orientation);
void	calc_move_top_costs(t_stack *stacki, int size_stack);
int		get_position(t_stack *stack, t_stack *node);
int		rotates_up(int pos, int size);
void	push_cheaper(t_data *data, t_stack *cheaper, int orientation);
void	rotate_to_top_a(t_data *data, t_stack *node);
void	rotate_to_top_b(t_data *data, t_stack *node);
void	sort_two_to_five(t_data *data);
void	sa(t_data *data);
int		is_sorted(t_stack *stack);

#endif
