/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:52:26 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/03 17:41:02 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate_b(t_stack *b, t_stack *a, int index, int size)
{
	if (index <= size / 2)
	{
		while (index > 0)
		{
			rb(b);
			write(1, "rb\n", 3);
			display(a, b);
			index--;
		}
	}
	else
	{
		index = size - index;
		while (index > 0)
		{
			rrb(b);
			write(1, "rrb\n", 3);
			display(a, b);
			index--;
		}
	}
}

int	is_in_middle(int index, int size)
{
	int	threshold;

	threshold = size / 5;
	if (index >= threshold && index < size - threshold)
		return (1);
	return (0);
}

int	find_insertion_index(t_stack *a, int value)
{
	t_node	*cur;
	int		index;

	if (!a || !a->top)
		return (0);
	if (value < a->top->data)
		return (0);
	cur = a->top;
	index = 0;
	while (cur->next)
	{
		if (cur->data <= value && cur->next->data >= value)
			return (index + 1);
		index++;
		cur = cur->next;
	}
	return (index + 1);
}

void	rotate_a_to_index(t_stack *a, t_stack *b, int insertion_index)
{
	int	size_a;
	int	i;

	size_a = stack_size(a);
	i = 0;
	if (insertion_index <= (size_a / 2))
	{
		while (i < insertion_index)
		{
			ra(a);
			write(1, "ra\n", 3);
			display(a, b);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < (size_a - insertion_index))
		{
			rra(a);
			write(1, "rra\n", 4);
			display(a, b);
			i++;
		}
	}
}

void	undo_a_rotation(t_stack *a, t_stack *b, int insertion_index)
{
	int	size_a;
	int	i;

	size_a = stack_size(a);
	i = 0;
	if (insertion_index <= (size_a - 1) / 2)
	{
		while (i < insertion_index + 1)
		{
			rra(a);
			write(1, "rra\n", 4);
			display(a, b);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < (size_a - 1 - insertion_index) + 1)
		{
			ra(a);
			write(1, "ra\n", 3);
			display(a, b);
			i++;
		}
	}
}

void	adjust_a(t_stack *a, t_stack *b)
{
	int	insertion_index;
	int	value;

	value = b->top->data;
	insertion_index = find_insertion_index(a, value);
	rotate_a_to_index(a, b, insertion_index);
	pa(a, b);
	write(1, "pa\n", 3);
	display(a, b);
	undo_a_rotation(a, b, insertion_index);
}
