/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:44:39 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/25 14:07:51 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_p(void *ptr, t_format *format)
{
	char	*str;
	char	*formatted_str;
	int		num_char;

	if (ptr == NULL)
	{
		str = "(nil)";
		return (write(1, str, 5));
	}
	str = ft_itoa_base((size_t)ptr, 16);
	if (!str)
		return (0);
	format->width -= 2;
	formatted_str = apply_flags(str, format, 'p');
	if (!formatted_str)
		return (0);
	num_char = write(1, "0x", 2);
	num_char += write(1, formatted_str, ft_strlen(formatted_str));
	free(formatted_str);
	return (num_char);
}
