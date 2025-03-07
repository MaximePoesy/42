/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:52:26 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/07 15:45:13 by mpoesy           ###   ########.fr       */
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

int	find_insertion_index(t_stack *a, int value)
{
	t_node	*cur;
	int		index;

	if (!a || !a->top)
		return (0);
	if (value < a->top->data)
		return (0);
	cur = a->top;
	index = 0;
	while (cur->next)
	{
		if (cur->data <= value && cur->next->data >= value)
			return (index + 1);
		cur = cur->next;
		index++;
	}
	return (index + 1);
}

int	is_in_middle(int index, int size)
{
	int	threshold;

	threshold = size / 5;
	if (index >= threshold && index < size - threshold)
		return (1);
	return (0);
}

/* calculate_move computes candidate and insertion indexes, rotations and cost */
t_move	calculate_move(t_stack *a, t_stack *b, int candidate_index)
{
	t_move	move;
	int		size_a;
	int		size_b;
	int		candidate_value;

	size_a = stack_size(a);
	size_b = stack_size(b);
	candidate_value = get_value_at_index(b, candidate_index);
	move.candidate_index = candidate_index;
	move.insertion_index = find_insertion_index(a, candidate_value);

	if (candidate_index <= size_b / 2)
		move.rotations_b = candidate_index;
	else
		move.rotations_b = size_b - candidate_index;

	if (move.insertion_index <= size_a / 2)
		move.rotations_a = move.insertion_index;
	else
		move.rotations_a = size_a - move.insertion_index;

	if ((candidate_index <= size_b / 2 && move.insertion_index <= size_a / 2) || (candidate_index > size_b / 2 && move.insertion_index > size_a / 2))
	{
		if (move.rotations_a > move.rotations_b)
		{
			move.rotations_ab = move.rotations_b;
			move.rotations_a -= move.rotations_ab;
			move.rotations_b -= move.rotations_ab;
			move.total_cost = move.rotations_a + move.rotations_ab;
		}
		else
		{
			move.rotations_ab = move.rotations_a;
			move.rotations_a -= move.rotations_ab;
                        move.rotations_b -= move.rotations_ab;
			move.total_cost = move.rotations_b + move.rotations_ab;
		}
	}
	else
		move.total_cost = move.rotations_a + move.rotations_b;
	return (move);
}

/* find_best_candidate scans B for the candidate with minimal cost */
int	find_best_candidate(t_stack *b, t_stack *a)
{
	int		i;
	int		size_b;
	int		best_index;
	t_move	move;
	t_move	best_move;

	size_b = stack_size(b);
	i = 0;
	best_move.total_cost = -1;
	best_index = 0;
	//display(a, b);
	while (i < size_b)
	{
		move = calculate_move(a, b, i);
		/*
		printf("move.candidate_index : %d\n", move.candidate_index);
		printf("actual value : %d\n", get_value_at_index(b, move.candidate_index));
		printf("move.insertion_index : %d\n", move.insertion_index);
		printf("move.rotations_a : %d\n", move.rotations_a);
		printf("move.rotations_b : %d\n", move.rotations_b);
		printf("move.rotations_ab : %d\n", move.rotations_ab);
		printf("move.total_cost : %d\n\n", move.total_cost);
		*/
		if (best_move.total_cost == -1 || move.total_cost < best_move.total_cost)
		{
			best_move = move;
			best_index = i;
		}
		i++;
	}
	return (best_index);
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
		{
                	rr(a, b);
                	write(1, "rr\n", 3);
		}
		else
		{
			rrr(a, b);
                        write(1, "rrr\n", 4);
		}
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
			write(1, "rb\n", 3);
			i--;
		}
	}
	else
	{
		i = move.rotations_b;
		while (i > 0)
		{
			rrb(b);
			write(1, "rrb\n", 3);
			i--;
		}
	}
}

