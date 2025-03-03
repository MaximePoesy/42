/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:52:26 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/03 17:41:02 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate_b(t_stack *b, t_stack *a, int index, int size)
{
	if (index <= size / 2)
	{
		while (index > 0)
		{
			rb(b);
			write(1, "rb\n", 3);
			display(a, b);
			index--;
		}
	}
	else
	{
		index = size - index;
		while (index > 0)
		{
			rrb(b);
			write(1, "rrb\n", 3);
			display(a, b);
			index--;
		}
	}
}

int	is_in_middle(int index, int size)
{
	int	threshold;

	threshold = size / 5;
	if (index >= threshold && index < size - threshold)
		return (1);
	return (0);
}

void	rotate_to_rank(t_stack *a, t_stack *b, int rank, int stack_size_a)
{
	int	i;

	if (rank < stack_size_a / 2)
	{
		i = 0;
		while (i < rank)
		{
			ra(a);
			write(1, "ra\n", 3);
			display(a, b);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < (stack_size_a - rank))
		{
			rra(a);
			write(1, "rra\n", 4);
			display(a, b);
			i++;
		}
	}
}

void    undo_rotation(t_stack *a, t_stack *b, int rank, int stack_size_a)
{
        int     i;

        if (rank < stack_size_a / 2)
        {
                i = 0;
                while (i < rank)
                {
                        rra(a);
                        write(1, "rra\n", 4);
                        display(a, b);
                        i++;
                }
        }
        else
        {
                i = 0;
                while (i < (stack_size_a - rank))
                {
                        ra(a);
                        write(1, "ra\n", 3);
                        display(a, b);
                        i++;
                }
        }
}

void	adjust_a(t_stack *a, t_stack *b, int rank)
{
	rotate_to_rank(a, b, rank, stack_size(a));
	pa(a, b);
	write(1, "pa\n", 3);
	display(a, b);
	undo_rotation(a, b, rank, stack_size(a));
}
