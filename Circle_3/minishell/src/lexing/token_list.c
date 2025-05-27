/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:45:09 by staverni          #+#    #+#             */
/*   Updated: 2025/04/29 19:33:06 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterates through a linked list of tokens and applies a function to
 * each token.
 *
 * This function takes a pointer to the head of a linked list of tokens and a
 * function pointer. It iterates through the list, applying the provided
 * function to each token in the list.
 *
 * @param lst Pointer to the head of the linked list of tokens.
 * @param f Function pointer to the function to be applied to each token.
 */
void	ft_token_iter(t_token *lst, void (*f)(t_token *))
{
	t_token	*current;
	t_token	*next;

	if (lst == NULL || f == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		f(current);
		current = next;
	}
}

/**
 * @brief Adds a new token to the end of a linked list of tokens.
 *
 * This function takes a pointer to the head of a linked list of tokens and a
 * new token. It adds the new token to the end of the list.
 *
 * @param alst Pointer to the head of the linked list of tokens.
 * @param new Pointer to the new token to be added.
 */
void	ft_token_add_back(t_token **alst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}
