/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:42:37 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 12:21:13 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// sa (swap a): Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void	_sa(t_stack *a)
{
	t_node	*first;
	t_node	*second;

	first = a->top;
	second = a->top->next;
	if (!a || !a->top || !a->top->next)
		return ;
	first->next = second->next;
	second->next = first;
	a->top = second;
}

void	sa(t_stack *a)
{
	_sa(a);
	write(1, "sa\n", 3);
}

// sb (swap b):
// Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.

void	_sb(t_stack *b)
{
	t_node	*first;
	t_node	*second;

	first = b->top;
	second = b->top->next;
	if (!b || !b->top || !b->top->next)
		return ;
	first->next = second->next;
	second->next = first;
	b->top = second;
}

void	sb(t_stack *b)
{
	_sb(b);
	write(1, "sb\n", 3);
}

// ss : sa and sb at the same time.

void	ss(t_stack *a, t_stack *b)
{
	_sa(a);
	_sb(b);
	write(1, "ss\n", 3);
}

// pa (push a): Take the first element at the top of b
// and put it at the top of a.
// Do nothing if b is empty.

void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!b || !b->top)
		return ;
	temp = b->top;
	b->top = b->top->next;
	temp->next = a->top;
	a->top = temp;
	write(1, "pa\n", 3);
}

// pb (push b): Take the first element at the top of a
// and put it at the top of b.
// Do nothing if a is empty.

void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!a || !a->top)
		return ;
	temp = a->top;
	a->top = a->top->next;
	temp->next = b->top;
	b->top = temp;
	write(1, "pb\n", 3);
}
