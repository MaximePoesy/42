#include "push_swap.h"

void	sort_three(t_stack *a)
{
	int	s;
	int	x;
	int	y;
	int	z;

	s = stack_size(a);
	if (s < 2)
		return ;
	if (s == 2)
	{
		if (a->top->data > a->top->next->data)
			sa(a);
		return ;
	}
	x = a->top->data;
	y = a->top->next->data;
	z = a->top->next->next->data;
	if (x < y && y < z)
		return ;
	if (x > y && x < z)
		sa(a);
	else if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && x > z)
		ra(a);
	else if (x < y && x > z)
		rra(a);
	else if (x < y && y > z)
	{
		sa(a);
		ra(a);
	}
}

/* rotate_a_individual rotates A individually to bring the insertion position to top */
void    rotate_b_back(t_move move, t_stack *b)
{
        int     size_b;
        int     i;

        size_b = stack_size(b);
        if (move.insertion_index <= size_b / 2)
        {
                i = move.rotations_b + move.rotations_ab;
                while (i > 0)
                {
                        rrb(b);
                        i--;
                }
        }
        else
        {
                i = move.rotations_b + move.rotations_ab + 1;
                while (i > 0)
                {
                        rb(b);
                        i--;
                }
        }
}

/* execute_best_move combines all rotations and pushes the candidate from B to A */
int	execute_best_move_atob(t_stack *a, t_stack *b, t_move move)
{
	int	rota_back;

	//double_rotate(move, a, b);
	rota_back = rotate_b_individual(move, b);
	rotate_a_individual(move, a);
	pb(a, b); 
	return (rota_back);
}

int	pushtob(t_stack *a, t_stack *b)
{
	t_move     best_candidate;
	int	rota_back;

	rota_back = 0;
	while (stack_size(a) > 1)
	{
		best_candidate = find_best_candidate_atob(b, a);
                rota_back += execute_best_move_atob(a, b, best_candidate);
	}
	//sort_three(a);
	return(rota_back);
}
