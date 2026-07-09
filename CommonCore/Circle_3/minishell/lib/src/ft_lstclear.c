/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:05:46 by staverni          #+#    #+#             */
/*   Updated: 2024/08/25 18:13:27 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p1;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		p1 = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = p1;
	}
	*lst = NULL;
}
