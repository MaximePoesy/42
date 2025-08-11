/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:24 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:26 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gets.h"

int	get_minimum(const t_stack *stack)
{
	int	i;
	int	minimum;

	i = 1;
	minimum = stack->p_array[0];
	while (i < stack->top)
	{
		if (stack->p_array[i] < minimum)
			minimum = stack->p_array[i];
		i++;
	}
	return (minimum);
}

int	get_maximum(const t_stack *stack)
{
	int	i;
	int	maximum;

	i = 1;
	maximum = stack->p_array[0];
	while (i < stack->top)
	{
		if (stack->p_array[i] > maximum)
			maximum = stack->p_array[i];
		i++;
	}
	return (maximum);
}

int	get_index(const t_stack *stack, int element)
{
	int	i;
	int	index_element;

	i = 0;
	index_element = -1;
	while (i < stack->top)
	{
		if (element == stack->p_array[i])
			index_element = i;
		i++;
	}
	return (index_element);
}
