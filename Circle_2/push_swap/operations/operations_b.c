/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:40:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 12:17:58 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.

void	_ra(t_stack *a)
{
	t_node	*temp;
	t_node	*last;

	if (!a || !a->top || !a->top->next)
		return ;
	temp = a->top;
	last = a->top;
	while (last->next != NULL)
		last = last->next;
	a->top = a->top->next;
	last->next = temp;
	temp->next = NULL;
}

void	ra(t_stack *a)
{
	_ra(a);
	write(1, "ra\n", 3);
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.

void	_rb(t_stack *b)
{
	t_node	*temp;
	t_node	*last;

	if (!b || !b->top || !b->top->next)
		return ;
	temp = b->top;
	last = b->top;
	while (last->next != NULL)
		last = last->next;
	b->top = b->top->next;
	last->next = temp;
	temp->next = NULL;
}

void    rb(t_stack *b)
{
        _rb(b);
        write(1, "rb\n", 3);
}

// rr : ra and rb at the same time.

void	rr(t_stack *a, t_stack *b)
{
	_ra(a);
	_rb(b);
	write(1, "rr\n", 3);
}
