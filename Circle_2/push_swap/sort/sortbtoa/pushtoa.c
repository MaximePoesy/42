#include "push_swap.h"

/* execute_best_move combines all rotations and pushes the candidate from B to A */
void	execute_best_move(t_stack *a, t_stack *b, t_move move)
{
	double_rotate(move, a, b);
	rotate_b_individual(move, b);
	rotate_a_individual(move, a);
	pa(a, b); 
	rotate_a_back(move, a);
}

void	pushtoa(t_stack *a, t_stack *b)
{
	t_move	best_candidate;

	while (stack_size(b) != 0)
	{
		best_candidate = find_best_candidate_btoa(b, a);
		//printf("Index of the best candidate : %d\n", best_candidate);
		execute_best_move(a, b, best_candidate);
	}
	rotate_a_back(move, a);
}
