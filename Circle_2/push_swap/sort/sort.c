/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:32:06 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/07 15:42:46 by mpoesy           ###   ########.fr       */
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

int	pushtob(t_stack *a, t_stack *b)
{
	int	count;

	count = 0;
	while (stack_size(a) > 1)
	{
		pb(a, b);
		write(1, "pb\n", 3);
		count++;
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
			write(1, "ra\n", 3);
			i--;
		}
	}
	else
	{
		i = move.rotations_a;
		while (i > 0)
		{
			rra(a);
			write(1, "rra\n", 4);
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
                        write(1, "rra\n", 4);
                        i--;
                }
        }
        else
        {
                i = move.rotations_a + move.rotations_ab + 1;
                while (i > 0)
                {
                        ra(a);
                        write(1, "ra\n", 3);
                        i--;
                }
        }
}

/* execute_best_move combines all rotations and pushes the candidate from B to A */
void	execute_best_move(t_stack *a, t_stack *b, int candidate_index)
{
	t_move	move;

	move = calculate_move(a, b, candidate_index);
	double_rotate(move, a, b);
	rotate_b_individual(move, b);
	rotate_a_individual(move, a);
	pa(a, b);
	write(1, "pa\n", 3);
	rotate_a_back(move, a);
}

void	sort(t_stack *a, t_stack *b)
{
	int	num;
	int	best_candidate;

	num = pushtob(a, b);
	while (stack_size(b) != 0)
	{
		best_candidate = find_best_candidate(b, a);
		//printf("Index of the best candidate : %d\n", best_candidate);
		execute_best_move(a, b, best_candidate);
	}
}
