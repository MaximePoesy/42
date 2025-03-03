/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:48:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/03 15:42:41 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				data;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
}					t_stack;

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
int					find_min_index(t_stack *b, int rank);
int					find_min_value(t_stack *b, int ignore_value);
int					pushtob(t_stack *a, t_stack *b);
int					stack_size(t_stack *stack);
void				adjust_a(t_stack *a, t_stack *b, int rank);
int					is_in_middle(int index, int size);
void				rotate_b(t_stack *b, t_stack *a, int index, int size);
void				display(t_stack *a, t_stack *b);
#endif
