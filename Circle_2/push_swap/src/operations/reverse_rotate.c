/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:33 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:34 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./operations.h"

static int	reverse_rotate(t_stack *stack)
{
	int	i;
	int	first_element;

	if (stack->top < 2)
		return (1);
	i = 0;
	first_element = stack->p_array[0];
	while (i < (stack->top - 1))
	{
		stack->p_array[i] = stack->p_array[i + 1];
		i++;
	}
	stack->p_array[stack->top - 1] = first_element;
	return (0);
}

void	reverse_rotate_a_or_b(t_stack *stack)
{
	reverse_rotate(stack);
	write(1, "rr", 2);
	write(1, &(stack->stack_name), 1);
	write(1, "\n", 1);
}

void	reverse_rotate_ab(t_stack *stack_a, t_stack *stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	write(1, "rrr\n", 4);
}
