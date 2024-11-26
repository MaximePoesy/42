/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:00:09 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/25 16:03:23 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static char	*apply_precision(char *str, t_format *format)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if (format->precision < 0 || format->precision >= len)
		return (ft_strdup(str));
	new_str = ft_calloc(format->precision + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, format->precision);
	return (new_str);
}

static char	*apply_space_flag(char *str, t_format *format, char specifier)
{
	char	*tmp;

	if (format->flags & FLAG_SPACE && (specifier == 'd' || specifier == 'i'
			|| specifier == 'u'))
	{
		if (str[0] != '-' && str[0] != '+')
		{
			tmp = str;
			str = (char *)malloc(ft_strlen(tmp) + 2);
			if (!str)
				return (NULL);
			str[0] = ' ';
			ft_strlcpy(str + 1, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	}
	return (str);
}

static char	*apply_plus_flag(char *str, t_format *format, char specifier)
{
	char	*tmp;

	if (format->flags & FLAG_PLUS && (specifier == 'd' || specifier == 'i'
			|| specifier == 'u'))
	{
		if (str[0] != '-' && str[0] != '+')
		{
			tmp = str;
			str = (char *)malloc(ft_strlen(tmp) + 2);
			if (!str)
				return (NULL);
			str[0] = '+';
			ft_strlcpy(str + 1, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	}
	return (str);
}
#include <stdio.h>

char *apply_flags(char *str, t_format *format, char specifier)
{
    char *new_str;

    new_str = apply_precision(str, format); 
    if (new_str != str)
        free(str);
    str = new_str;
    new_str = apply_width_and_padding(str, format, specifier);
    if (new_str != str)
        free(str);
    str = new_str;
    new_str = apply_space_flag(str, format, specifier);
    if (new_str != str)
        free(str);
    str = new_str;
    new_str = apply_plus_flag(str, format, specifier);
    if (new_str != str)
        free(str);
    return (new_str);
}

