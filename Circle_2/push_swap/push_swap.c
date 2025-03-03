/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:50:24 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/03 14:52:05 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(t_stack *s)
{
	s->top = NULL;
}

int	is_empty(t_stack *s)
{
	return (s->top == NULL);
}

void	push(t_stack *s, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->data = value;
	new_node->next = s->top;
	s->top = new_node;
}

int	pop(t_stack *s)
{
	t_node	*temp;
	int		value;

	if (is_empty(s))
	{
		printf("tu peux pas pop c est vide frero\n");
		return (-1);
	}
	temp = s->top;
	value = temp->data;
	s->top = s->top->next;
	free(temp);
	return (value);
}

void	display(t_stack *a, t_stack *b)
{
	t_node	*current_a;
	t_node	*current_b;

	current_a = a->top;
	current_b = b->top;
	printf("    STACK A\t\tSTACK B\n\n");
	while (current_a || current_b)
	{
		if (current_a)
		{
			printf("       %-20d", current_a->data);
			current_a = current_a->next;
		}
		else
			printf("                           ");
		if (current_b)
		{
			printf("%d\n", current_b->data);
			current_b = current_b->next;
		}
		else
			printf("\n");
	}
	printf("\n");
}

void	free_stack(t_stack *s)
{
	while (!is_empty(s))
	{
		pop(s);
	}
}

int	main(void)
{
	t_stack a, b;
	init_stack(&a);
	init_stack(&b);
	push(&a, 1);
	push(&a, 5);
	push(&a, 3);
	push(&a, 9);
	push(&a, 2);
	push(&a, 8);
	display(&a, &b);
	sort(&a, &b);
	printf("---------- FINAL STACK ! ----------\n\n");
	display(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
