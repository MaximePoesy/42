/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:32:06 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 15:52:42 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_size(t_stack *stack)
{
	int		count;
	t_node	*current;

	count = 0;
	current = stack->top;
	while (current)
	{
		count++;
		current = current->next;
	}

	return (count);
}

/* rotate_a_individual rotates A individually to bring the insertion position to top */
void	rotate_a_individual(t_move move, t_stack *a)
{
	int	size_a;
	int	i;

	size_a = stack_size(a);
	if (move.insertion_index <= size_a / 2)
	{
		i = move.rotations_a;
		while (i > 0)
		{
			ra(a);
			i--;
		}
	}
	else
	{
		i = move.rotations_a;
		while (i > 0)
		{
			rra(a);
			i--;
		}
	}
}

/* rotate_a_individual rotates A individually to bring the insertion position to top */
void    rotate_a_back(t_move move, t_stack *a)
{
        int     size_a;
        int     i;

        size_a = stack_size(a);
        if (move.insertion_index <= size_a / 2)
        {
                i = move.rotations_a + move.rotations_ab;
                while (i > 0)
                {
                        rra(a);
                        i--;
                }
        }
        else
        {
                i = move.rotations_a + move.rotations_ab + 1;
                while (i > 0)
                {
                        ra(a);
                        i--;
                }
        }
}

void	sort(t_stack *a, t_stack *b)
{
	pushtob(a, b);
	display(a,b);
	pushtoa(a, b);
}
