/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:05 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 11:06:51 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "../struct.h"
# include "../gets/gets.h"
# include "../random/random.h"
# include "../operations/operations.h"
# include "../utilities_algorithms/utilities_algorithms.h"
# include <stdlib.h>
# include <stdio.h>
# include "../setup_stacks/setup_stacks.h"

// sort_three.c
void	sort_three(t_stack *stack_a);

//  sort_five.c
void	sort_five(t_stack *stack_a, t_stack *stack_b);

// bubble_sort.c
void	bubble_sort_norm(t_stack *stack_a, t_stack *stack_b);

// radix_sort.c
void	copy_stack_a_to_b(const t_stack *stack_a, t_stack *stack_b);
void	convert_stack_a_to_positive_ints(t_stack *stack_a,
			const t_stack *stack_b);
void	radix_sort(t_stack *stack_a, t_stack *stack_b);

// sort_large.c
void	sort_large(t_stack *stack_a, t_stack *stack_b);

#endif /* ALGORITHMS_H */
