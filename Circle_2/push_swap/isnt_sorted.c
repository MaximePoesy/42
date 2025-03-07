/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isnt_sorted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:46:41 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/06 14:56:39 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	isnt_sorted(t_stack *a)
{
	t_node	*current;

	if (!a || !a->top || !a->top->next)
	{
		return (0);
	}
	current = a->top;
	while (current->next)
	{
		if (current->data > current->next->data)
			return (1);
		current = current->next;
	}
	return (0);
}
