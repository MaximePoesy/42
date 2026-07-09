/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:30 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:32 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./operations.h"

int	push(t_stack *origin_stack, t_stack *destination_stack)
{
	int	first_element;

	write(1, "p", 1);
	write(1, &(destination_stack->stack_name), 1);
	write(1, "\n", 1);
	if (origin_stack->top == 0)
		return (1);
	first_element = origin_stack->p_array[origin_stack->top - 1];
	origin_stack->top--;
	destination_stack->p_array[destination_stack->top] = first_element;
	destination_stack->top++;
	return (0);
}
