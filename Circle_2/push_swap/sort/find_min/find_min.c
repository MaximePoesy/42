/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:40:02 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/05 17:40:30 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	find_overall_min(t_stack *b)
{
	t_node	*cur;
	int		min;

	min = __INT_MAX__;
	cur = b->top;
	while (cur)
	{
		if (cur->data < min)
			min = cur->data;
		cur = cur->next;
	}
	return (min);
}

int	get_index(t_stack *b, int value)
{
	t_node	*cur;
	int		index;

	cur = b->top;
	index = 0;
	while (cur)
	{
		if (cur->data == value)
			return (index);
		index++;
		cur = cur->next;
	}
	return (-1);
}

int	find_next_min_value(t_stack *b, int current_min)
{
	t_node	*cur;
	int		next_min;

	next_min = __INT_MAX__;
	cur = b->top;
	while (cur)
	{
		if (cur->data > current_min && cur->data < next_min)
			next_min = cur->data;
		cur = cur->next;
	}
	if (next_min == __INT_MAX__)
		return (current_min);
	return (next_min);
}

int	find_min_index(t_stack *b)
{
	int	size;
	int	candidate;
	int	candidate_index;
	int	next_candidate;

	size = stack_size(b);
	candidate = find_overall_min(b);
	candidate_index = get_index(b, candidate);
	while (is_in_middle(candidate_index, size))
	{
		next_candidate = find_next_min_value(b, candidate);
		if (next_candidate == candidate)
			break ;
		candidate = next_candidate;
		candidate_index = get_index(b, candidate);
	}
	return (candidate_index);
}
