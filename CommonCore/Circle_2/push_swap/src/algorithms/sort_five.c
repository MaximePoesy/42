/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:09 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:11 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./algorithms.h"

static long long	*create_distance_array(const t_stack *stack, int origin)
{
	int			i;
	long long	*p_distance_array;

	p_distance_array = malloc(sizeof(*p_distance_array) * stack->len);
	if (p_distance_array == NULL)
	{
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < stack->top)
	{
		p_distance_array[i] = (long long)stack->p_array[i] - origin;
		i++;
	}
	return (p_distance_array);
}

static int	get_minimum_positive(const t_stack *stack,
		long long *p_distance_array)
{
	int	i;
	int	minimum_positive;

	i = 0;
	while ((i < stack->top) && (p_distance_array[i] < 0))
		i++;
	if (i == stack->top)
	{
		return (-1);
	}
	minimum_positive = stack->p_array[i];
	i++;
	while (i < stack->top)
	{
		if ((stack->p_array[i] < minimum_positive)
			&& (p_distance_array[i] > -1))
			minimum_positive = stack->p_array[i];
		i++;
	}
	return (minimum_positive);
}

static int	get_insert_value(const t_stack *destination_stack, int origin)
{
	int			insert_value;
	long long	*p_distance_array;

	p_distance_array = create_distance_array(destination_stack, origin);
	if (origin < get_minimum(destination_stack))
	{
		insert_value = get_minimum(destination_stack);
		free(p_distance_array);
		return (insert_value);
	}
	if (origin > get_maximum(destination_stack))
	{
		insert_value = get_minimum(destination_stack);
		free(p_distance_array);
		return (insert_value);
	}
	insert_value = get_minimum_positive(destination_stack, p_distance_array);
	if (insert_value == -1)
	{
		insert_value = destination_stack->p_array[0];
	}
	free(p_distance_array);
	return (insert_value);
}

static void	insert_into_stack(t_stack *origin_stack, t_stack *destination_stack)
{
	int	insert_value;

	insert_value = get_insert_value(destination_stack,
			origin_stack->p_array[origin_stack->top - 1]);
	rotate_to_top(destination_stack, insert_value);
	push(origin_stack, destination_stack);
}

void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	push(stack_a, stack_b);
	push(stack_a, stack_b);
	sort_three(stack_a);
	insert_into_stack(stack_b, stack_a);
	insert_into_stack(stack_b, stack_a);
	rotate_to_top(stack_a, get_minimum(stack_a));
}
