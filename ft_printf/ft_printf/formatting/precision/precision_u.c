/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:32:26 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/28 16:11:23 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

char	*precision_u(char *str, t_format *format)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if (format->precision < 0 || format->precision <= len)
		return (ft_strdup(str));
	new_str = ft_calloc(format->precision + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', format->precision - len);
	ft_memcpy(new_str + (format->precision - len), str, len);
	return (new_str);
}
