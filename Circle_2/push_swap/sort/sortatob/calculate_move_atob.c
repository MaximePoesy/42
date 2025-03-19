#include "push_swap.h"

int	find_insertion_index_atob(t_stack *b, int value)
{
	t_node	*cur;
	int		index;
	int		min;
	int		max;

	if (!b || !b->top)
		return (0);
	max = b->top->data;
	min = b->top->data;
	cur = b->top;
	while (cur)
	{
		if (cur->data > max)
			max = cur->data;
		if (cur->data < min)
			min = cur->data;
		cur = cur->next;
	}
	if (value > max || value < min)
		return (0);
	cur = b->top;
	index = 0;
	while (cur->next)
	{
		if (cur->data >= value && cur->next->data <= value)
			return (index + 1);
		cur = cur->next;
		index++;
	}
	return (0);
}


t_move	calculate_move_atob(t_stack *a, t_stack *b, int candidate_index)
{
	t_move	move;
	int		size_a;
	int		size_b;
	int		candidate_value;

	size_a = stack_size(a);
	size_b = stack_size(b);
	candidate_value = get_value_at_index(a, candidate_index);
	move.candidate_index = candidate_index;
	move.insertion_index = find_insertion_index_atob(b, candidate_value);
	if (candidate_index <= size_a / 2)
		move.rotations_a = candidate_index;
	else
		move.rotations_a = size_a - candidate_index;
	if (move.insertion_index <= size_b / 2)
		move.rotations_b = move.insertion_index;
	else
		move.rotations_b = size_b - move.insertion_index;
	/*
	if ((candidate_index <= size_b / 2 && move.insertion_index <= size_a / 2)
		|| (candidate_index > size_b / 2 && move.insertion_index > size_a / 2))
	{
		if (move.rotations_b > move.rotations_a)
		{
			move.rotations_ab = move.rotations_a;
			move.rotations_b = move.rotations_b - move.rotations_ab;
			move.rotations_a = 0;
			move.total_cost = move.rotations_b + move.rotations_ab;
		}
		else
		{
			move.rotations_ab = move.rotations_b;
			move.rotations_a = move.rotations_a - move.rotations_ab;
			move.rotations_b = 0;
			move.total_cost = move.rotations_a + move.rotations_ab;
		}
	}
	else
	{
		move.rotations_ab = 0;
		move.total_cost = move.rotations_a + move.rotations_b;
	}
	*/
	move.total_cost = move.rotations_a + move.rotations_b;
	/*
	printf("a : %d - b : %d - ab : %d", move.rotations_a, move.rotations_b, move.rotations_ab);
	pause();
	*/
	return (move);
}
