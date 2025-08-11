/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:35 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:36 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./operations.h"

static int	rotate(t_stack *stack)
{
	int	i;
	int	last_element;

	if (stack->top < 2)
		return (1);
	i = stack->top - 1;
	last_element = stack->p_array[stack->top - 1];
	while (i > 0)
	{
		stack->p_array[i] = stack->p_array[i - 1];
		i--;
	}
	stack->p_array[0] = last_element;
	return (0);
}

void	rotate_a_or_b(t_stack *stack)
{
	rotate(stack);
	write(1, "r", 1);
	write(1, &(stack->stack_name), 1);
	write(1, "\n", 1);
}

void	rotate_ab(t_stack *stack_a, t_stack *stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
}
