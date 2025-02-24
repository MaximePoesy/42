/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:40:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/24 17:17:03 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.

void	ra(t_stack *a)
{
	t_node	*temp;
	t_node	*last;

	if (!a || !a->top)
		return ;
	temp = a->top;
	last = a->top;
	while (last->next != NULL)
		last = last->next;
	a->top = a->top->next;
	last->next = temp;
	temp->next = NULL;
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.

void	rb(t_stack *b)
{
	t_node	*temp;
	t_node	*last;

	if (!b || !b->top)
		return ;
	temp = b->top;
	last = b->top;
	while (last->next != NULL)
		last = last->next;
	b->top = b->top->next;
	last->next = temp;
	temp->next = NULL;
}

// rr : ra and rb at the same time.

void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	rb(b);
}
