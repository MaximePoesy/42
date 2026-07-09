/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:38 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:08:04 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack *stack_a, t_stack *stack_b, int argc)
{
	if (is_sorted(stack_a))
		return ;
	if (is_ordered(stack_a))
	{
		rotate_to_top(stack_a, get_minimum(stack_a));
		return ;
	}
	if (argc == 3 || argc == 4)
		sort_three(stack_a);
	else if (argc == 5 || argc == 6)
		sort_five(stack_a, stack_b);
	else
		sort_large(stack_a, stack_b);
}

int	main(int argc, char *argv[])
{
	t_stack	stacks[2];
	int		is_malloc_failed;

	is_malloc_failed = 0;
	if (argc <= 1)
		exit(EXIT_FAILURE);
	check_for_int_and_overflow(argc, argv);
	is_malloc_failed = initialize_stack(&(stacks[A]), argc - 1, 'a');
	if (is_malloc_failed)
		exit(EXIT_FAILURE);
	populate_stack(argc, argv, &(stacks[A]));
	is_malloc_failed = initialize_stack(&(stacks[B]), argc - 1, 'b');
	if (is_malloc_failed)
	{
		free(stacks[A].p_array);
		exit(EXIT_FAILURE);
	}
	exit_if_duplicate(&(stacks[A]), &(stacks[B]));
	push_swap(&(stacks[A]), &(stacks[B]), argc);
	free_stacks(&(stacks[A]), &(stacks[B]));
	return (0);
}
