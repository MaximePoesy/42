/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:52:26 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 15:43:41 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_value_at_index(t_stack *stack, int index)
{
	t_node	*current;
	int		i;

	if (!stack || !stack->top)
		return (0);
	current = stack->top;
	i = 0;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	if (current)
		return (current->data);
	return (0);
}

int	is_in_middle(int index, int size)
{
	int	threshold;

	threshold = size / 5;
	if (index >= threshold && index < size - threshold)
		return (1);
	return (0);
}

/* double_rotate performs combined rotations on A and B as long as possible */
void    double_rotate(t_move move, t_stack *a, t_stack *b)
{
        int     size_a;
        int     i;

        size_a = stack_size(a);
	i = move.rotations_ab;
	while (i > 0)
        {
		if (move.insertion_index <= size_a / 2)
                	rr(a, b);
		else
			rrr(a, b);
                i--;
        }
}

/* rotate_b_individual rotates B individually to bring the candidate to top */
void	rotate_b_individual(t_move move, t_stack *b)
{
	int	size_b;
	int	i;

	size_b = stack_size(b);
	if (move.candidate_index <= size_b / 2)
	{
		i = move.rotations_b;
		while (i > 0)
		{
			rb(b);
			i--;
		}
	}
	else
	{
		i = move.rotations_b;
		while (i > 0)
		{
			rrb(b);
			i--;
		}
	}
}

