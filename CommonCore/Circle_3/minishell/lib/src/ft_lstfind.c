/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:57:36 by staverni          #+#    #+#             */
/*   Updated: 2025/04/20 12:11:36 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds a node in a linked list that matches a given reference data.
 *
 * This function iterates through the linked list and compares each node's
 * content with the provided reference data using the provided comparison
 * function. If a match is found, it returns the matching node.
 *
 * @param lst Pointer to the head of the linked list.
 * @param data_ref Pointer to the reference data to compare against.
 * @param cmp Function pointer to the comparison function.
 * @return t_list* Pointer to the matching node, or NULL if not found.
 */
t_list	*ft_lstfind(t_list *lst, void *data_ref,
	int (*cmp)(const void *, const void *))
{
	t_list	*current;

	if (!lst || !data_ref || !cmp)
		return (NULL);
	current = lst;
	while (current)
	{
		if (cmp(current->content, data_ref) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
