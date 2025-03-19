/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_candidate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:48:55 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 16:49:26 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* find_best_candidate scans B for the candidate with minimal cost */
t_move	find_best_candidate_atob(t_stack *b, t_stack *a)
{
	int		i;
	int		size;
	t_move	move;
	t_move	best_move;

	size = stack_size(a);
	i = 0;
	best_move.total_cost = -1;
	display(a, b);
	while (i < size)
	{
		move = calculate_move_atob(a, b, i);
		
		printf("move.candidate_index : %d\n", move.candidate_index);
		printf("actual value : %d\n", get_value_at_index(b, move.candidate_index));
		printf("move.insertion_index : %d\n", move.insertion_index);
		printf("move.rotations_a : %d\n", move.rotations_a);
		printf("move.rotations_b : %d\n", move.rotations_b);
		printf("move.rotations_ab : %d\n", move.rotations_ab);
		printf("move.total_cost : %d\n\n", move.total_cost);
		
		if (best_move.total_cost == -1 || move.total_cost < best_move.total_cost)
			best_move = move;
		i++;
	}
	return (best_move);
}
