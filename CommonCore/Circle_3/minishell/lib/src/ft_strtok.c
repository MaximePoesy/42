/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:59:26 by staverni          #+#    #+#             */
/*   Updated: 2025/03/17 16:59:49 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*token;

	if (!str && !last)
		return (NULL);
	if (!str)
		str = last;
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		last = str;
		return (NULL);
	}
	token = str;
	str = ft_strpbrk(str, delim);
	if (str == NULL)
		last = NULL;
	else
	{
		*str = '\0';
		last = str + 1;
	}
	return (token);
}
