/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:12 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:19 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./algorithms.h"

void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	copy_stack_a_to_b(stack_a, stack_b);
	bubble_sort_norm(stack_a, stack_b);
	convert_stack_a_to_positive_ints(stack_a, stack_b);
	radix_sort(stack_a, stack_b);
}
