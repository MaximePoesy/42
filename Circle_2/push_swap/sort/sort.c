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

int	find_min_value(t_stack *b, int ignore_value)
{
	t_node	*current;
	int		min_value;

	min_value = __INT_MAX__;
	current = b->top;
	while (current)
	{
		if (current->data < min_value && current->data > ignore_value)
			min_value = current->data;
		current = current->next;
	}
	return (min_value);
}

int	find_min_index(t_stack *b, int rank)
{
	t_node	*current;
	int		min_value;
	int		index;
	int		k;

	min_value = -__INT_MAX__;
	k = 0;
	while (k <= rank)
	{
		min_value = find_min_value(b, min_value);
		current = b->top;
		index = 0;
		while (current)
		{
			if (current->data == min_value)
				break ;
			current = current->next;
			index++;
		}
		k++;
	}
	return (index);
}

void	sort(t_stack *a, t_stack *b)
{
	int	num;
	int	min_index;
	int	size_b;
	int	min_rank;

	num = pushtob(a, b);
	min_rank = 0;
	while (stack_size(b) != 0)
	{
		size_b = stack_size(b);
		min_index = find_min_index(b, min_rank);
		if (is_in_middle(min_index, size_b))
		{
			min_rank++;
			continue ;
		}
		rotate_b(b, a, min_index, size_b);
		adjust_a(a, b, min_rank);
		min_rank = 0;
	}
}
