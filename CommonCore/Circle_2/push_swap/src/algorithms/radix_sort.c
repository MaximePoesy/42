/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:02 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:08 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./algorithms.h"

void	copy_stack_a_to_b(const t_stack *stack_a, t_stack *stack_b)
{
	int	i;

	i = 0;
	while (i < stack_a->top)
	{
		stack_b->p_array[i] = stack_a->p_array[i];
		i++;
	}
}

void	convert_stack_a_to_positive_ints(t_stack *stack_a,
		const t_stack *stack_b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < stack_a->top)
	{
		while (j < stack_a->top)
		{
			if (stack_a->p_array[i] == stack_b->p_array[j])
			{
				stack_a->p_array[i] = j;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static int	get_place_most_significant_set_bit(int x)
{
	int	bits;

	bits = 0;
	while (x >> bits != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	most_significant_set_bit;
	int	current_bit;
	int	j;
	int	top_dup;

	most_significant_set_bit = get_place_most_significant_set_bit(stack_a->top);
	current_bit = 0;
	j = 0;
	top_dup = stack_a->top;
	while (current_bit < most_significant_set_bit)
	{
		while (j < top_dup)
		{
			if (((stack_a->p_array[stack_a->top - 1] >> current_bit) & 1) == 1)
				rotate_a_or_b(stack_a);
			else
				push(stack_a, stack_b);
			j++;
		}
		while (stack_b->top)
			push(stack_b, stack_a);
		j = 0;
		current_bit++;
	}
}
