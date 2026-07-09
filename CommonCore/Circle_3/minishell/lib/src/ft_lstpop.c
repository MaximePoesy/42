/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:27:59 by staverni          #+#    #+#             */
/*   Updated: 2025/04/20 11:59:06 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Removes the first node from the list that matches the reference value
 *        using the provided comparison function and deletes it using the
 *        provided deletion function.
 *
 * @param lst Pointer to the head of the list.
 * @param ref Reference value to compare against.
 * @param cmp Comparison function to determine if a node matches the reference.
 * @param del Deletion function to free the content of the node.
 *
 * @return 0 if a node was removed, 1 if no matching node was found or an error
 *         occurred.
 */
int	ft_lstpop(t_list **lst, void *ref, int (*cmp)(void *, void *),
	void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !cmp || !*lst || !del)
		return (1);
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (cmp(current->content, ref) == 0)
		{
			if (prev == NULL)
				*lst = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, del);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
