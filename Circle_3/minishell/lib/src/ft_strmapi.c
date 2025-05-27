/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:05:31 by staverni          #+#    #+#             */
/*   Updated: 2024/10/25 14:37:00 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_map;
	int		s_len;
	int		i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	s_map = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s_map)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_map[i] = f(i, s[i]);
		i++;
	}
	s_map[s_len] = '\0';
	return (s_map);
}
