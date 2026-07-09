/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:06:36 by staverni          #+#    #+#             */
/*   Updated: 2025/03/18 13:42:03 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (ft_strchr(charset, *s++) == NULL)
			++count;
		else
			return (count);
	}
	return (count);
}
