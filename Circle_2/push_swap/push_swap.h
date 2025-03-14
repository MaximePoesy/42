/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:48:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/13 14:41:53 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define INT_MAX 2147483647
# define INT_MIN (-2147483648)

typedef struct s_node
{
	int				data;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
}					t_stack;

typedef struct s_move
{
	int	candidate_index;
	int	insertion_index;
	int	rotations_a;
	int	rotations_b;
	int	rotations_ab;
	int	total_cost;
}			t_move;

void				sa(t_stack *a);
void				sb(t_stack *b);
void				ss(t_stack *a, t_stack *b);
void				pa(t_stack *a, t_stack *b);
void				pb(t_stack *a, t_stack *b);
void				ra(t_stack *a);
void				rb(t_stack *b);
void				rr(t_stack *a, t_stack *b);
void				rra(t_stack *a);
void				rrb(t_stack *b);
void				rrr(t_stack *a, t_stack *b);
void				sort(t_stack *a, t_stack *b);
void					pushtob(t_stack *a, t_stack *b);
int					stack_size(t_stack *stack);
void				display(t_stack *a, t_stack *b);
t_move  calculate_move(t_stack *a, t_stack *b, int candidate_index);
t_move     find_best_candidate(t_stack *b, t_stack *a);
void    double_rotate(t_move move, t_stack *a, t_stack *b);
void    rotate_b_individual(t_move move, t_stack *b);
int     get_value_at_index(t_stack *stack, int index);
int     find_insertion_index(t_stack *a, int value);
int					parse_args(int argc, char **argv, t_stack *stack);
int	isnt_sorted(t_stack *a);
void    execute_best_move_atob(t_stack *a, t_stack *b, t_move move);
void    execute_best_move_btoa(t_stack *a, t_stack *b, t_move move);
t_move	find_best_candidate_atob(t_stack *b, t_stack *a);
t_move	find_best_candidate_btoa(t_stack *b, t_stack *a);
t_move	calculate_move_btoa(t_stack *a, t_stack *b, int candidate_index);
t_move	calculate_move_atob(t_stack *a, t_stack *b, int candidate_index);
void	pushtob(t_stack *a, t_stack *b);
void	pushtoa(t_stack *a, t_stack *b);
void	rotate_a_individual(t_move move, t_stack *a);
void    rotate_a_back(t_move move, t_stack *a);
#endif
