/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:54 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 12:19:08 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.

void	_rra(t_stack *a)
{
	t_node	*last;
	t_node	*before_last;

	if (!a || !a->top || !a->top->next)
		return ;
	before_last = a->top;
	while (before_last->next->next)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	last->next = a->top;
	a->top = last;
}

void	rra(t_stack *a)
{
	_rra(a);
	write(1, "rra\n", 4);
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one

void	_rrb(t_stack *b)
{
	t_node	*last;
	t_node	*before_last;

	if (!b || !b->top || !b->top->next)
		return ;
	before_last = b->top;
	while (before_last->next->next)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	last->next = b->top;
	b->top = last;
}

void    rrb(t_stack *b)
{
        _rrb(b);
        write(1, "rrb\n", 4);
}

// rrr : rra and rrb at the same time.

void	rrr(t_stack *a, t_stack *b)
{
	_rra(a);
	_rrb(b);
	write(1, "rrr\n", 4);
}
