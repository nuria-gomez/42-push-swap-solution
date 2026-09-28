#include "push_swap.h"

int	ft_error_data(t_data *data)
{
	clear_stacks(&data->stack_a);
	clear_stacks(&data->stack_b);
	write(2, "Error\n", 6);
	exit(1);
}

void	free_darr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}


int	ft_error(int error_code)
{
	write(2, "Error\n", 6);
	exit(error_code);
}