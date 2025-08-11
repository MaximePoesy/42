/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_algorithms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:41 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:51 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities_algorithms.h"

int	rotate_to_top(t_stack *stack, int element)
{
	int	number_of_rotations;
	int	index_element;
	int	middle_of_stack;

	number_of_rotations = 0;
	index_element = get_index(stack, element);
	middle_of_stack = (stack->top - 1) / 2;
	while (get_index(stack, element) != stack->top - 1)
	{
		if (index_element < middle_of_stack)
			reverse_rotate_a_or_b(stack);
		else
			rotate_a_or_b(stack);
		number_of_rotations++;
	}
	return (number_of_rotations);
}
