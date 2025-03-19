#include "push_swap.h"

/* execute_best_move combines all rotations and pushes the candidate from B to A */
int	execute_best_move(t_stack *a, t_stack *b, t_move move)
{
	int	rota_back;

	//double_rotate(move, a, b);
	rotate_b_individual(move, b);
	rota_back = rotate_a_individual(move, a);
	pa(a, b);
	return (rota_back);
}

void	pushtoa(t_stack *a, t_stack *b)
{
	int	rota_back;
	t_move	best_candidate;

	rota_back = 0;
	while (stack_size(b) != 0)
	{
		best_candidate = find_best_candidate_btoa(b, a);
		//printf("Index of the best candidate : %d\n", best_candidate);
		rota_back += execute_best_move(a, b, best_candidate);
	}
	while (rota_back < 0)
	{
		rra(a);
		rota_back++;
	}
	while (rota_back > 0)
	{
		ra(a);
		rota_back--;
	}

	//rotate_a_back(move, a);
}
