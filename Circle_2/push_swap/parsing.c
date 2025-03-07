/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:52:53 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/06 14:56:46 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Checks if a string is a valid integer
int	is_valid_number(const char *str)
{
	long	num;
	int		sign;

	if (!str || !*str)
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	num = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = num * 10 + (*str - '0');
		if ((num * sign) > INT_MAX || (num * sign) < INT_MIN)
			return (0);
		str++;
	}
	return (1);
}

// Checks for duplicate numbers
int	has_duplicates(t_stack *stack)
{
	t_node	*outer;
	t_node	*inner;

	outer = stack->top;
	while (outer)
	{
		inner = outer->next;
		while (inner)
		{
			if (outer->data == inner->data)
				return (1);
			inner = inner->next;
		}
		outer = outer->next;
	}
	return (0);
}

// Adds a new node to the stack
void	push_to_stack(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->data = value;
	new_node->next = stack->top;
	stack->top = new_node;
}

// Parses arguments main function
int	parse_args(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	value;
	char	**tmp_array;

	tmp_array = argv;
	i = argc - 1;
	while (i > 0)
	{
		if (!is_valid_number(tmp_array[i]))
		{
			return (0);
		}
		value = ft_atoi(tmp_array[i]);
		push_to_stack(stack, value);
		i--;
	}
	if (has_duplicates(stack))
		return (0);
	return (1);
}
