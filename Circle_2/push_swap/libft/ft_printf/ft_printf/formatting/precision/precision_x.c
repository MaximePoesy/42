/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:33:34 by mpoesy            #+#    #+#             */
/*   Updated: 2024/12/04 15:58:12 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

char	*precision_x(char *str, t_format *format)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if (format->precision == 0 && str[0] == '0' && str[1] == '\0')
		return (ft_strdup(""));
	if (format->precision == (size_t)-1 || format->precision <= len)
		return (ft_strdup(str));
	if (format->precision > 2147483648)
		return (NULL);
	new_str = ft_calloc(format->precision + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', format->precision - len);
	ft_memcpy(new_str + (format->precision - len), str, len);
	return (new_str);
}
