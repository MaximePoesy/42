/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:32:06 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/03 15:54:27 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_size(t_stack *stack)
{
	int		count;
	t_node	*current;

	count = 0;
	current = stack->top;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	pushtob(t_stack *a, t_stack *b)
{
	int	count;

	count = 0;
	while (stack_size(a) > 0)
	{
		pb(a, b);
		write(1, "pb\n", 3);
		display(a, b);
		count++;
	}
	return (count);
}

void	sort(t_stack *a, t_stack *b)
{
	int	num;
	int	min_index;
	int	size_b;

	num = pushtob(a, b);
	while (stack_size(b) != 0)
	{
		size_b = stack_size(b);
		min_index = find_min_index(b);
		rotate_b(b, a, min_index, size_b);
		adjust_a(a, b);
	}
}
