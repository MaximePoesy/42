#include "push_swap.h"

int	find_insertion_index_btoa(t_stack *a, int value)
{
	t_node	*cur;
	int		index;
	int		min;
	int		max;

	if (!a || !a->top)
		return (0);
	min = a->top->data;
	max = a->top->data;
	cur = a->top;
	while (cur)
	{
		if (cur->data < min)
			min = cur->data;
		if (cur->data > max)
			max = cur->data;
		cur = cur->next;
	}
	if (value < min || value > max)
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
	return (0);
}

/* calculate_move computes candidate and insertion indexes, rotations and cost */
t_move	calculate_move_btoa(t_stack *a, t_stack *b, int candidate_index)
{
	t_move	move;
	int		size_a;
	int		size_b;
	int		candidate_value;

	size_a = stack_size(a);
	size_b = stack_size(b);
	candidate_value = get_value_at_index(b, candidate_index);
	move.candidate_index = candidate_index;
	move.insertion_index = find_insertion_index_btoa(a, candidate_value);

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
	{
		move.rotations_ab = 0;
		move.total_cost = move.rotations_a + move.rotations_b;
	}
	return (move);
}
