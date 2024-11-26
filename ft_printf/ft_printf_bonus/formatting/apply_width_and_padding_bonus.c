/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_width_and_padding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:08:13 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/22 16:10:40 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static int	calculate_string_length(char *str, char specifier)
{
	if (str == NULL)
		return (0);
	if (specifier == 'c' && *str == '\0')
		return (1);
	return (ft_strlen(str));
}

static void	set_padding_and_total(int len_str, t_format *format,
		int *padding_len, int *total_len)
{
	*total_len = len_str;
	*padding_len = 0;
	if (format->width > len_str)
	{
		*total_len = format->width;
		*padding_len = format->width - len_str;
	}
}

static char	*allocate_string(int padding_len, char *str, t_format *format,
		int total_len)
{
	if (padding_len <= 0 || !format->iswidthsetup)
		return (ft_strdup(str));
	return (malloc(total_len + 1));
}

static void	apply_padding(char *final_str, int *index, int padding_len,
		char pad_char)
{
	while (padding_len > 0)
	{
		final_str[*index] = pad_char;
		(*index)++;
		padding_len--;
	}
}

static void	copy_char_with_sign(char *final_str, char **str, int *index)
{
	if (**str == '-')
	{
		final_str[*index] = '-';
		(*index)++;
		(*str)++;
	}
}

static void	copy_content(char *final_str, char *str, int *index)
{
	while (*str)
	{
		final_str[*index] = *str;
		(*index)++;
		str++;
	}
}

static void	handle_left_padding(char *final_str, char *str, int *index,
		int padding_len, t_format *format)
{
	char	pad_char;

	pad_char = ' ';
	if (format->flags & FLAG_ZERO)
		pad_char = '0';
	copy_char_with_sign(final_str, &str, index);
	apply_padding(final_str, index, padding_len, pad_char);
	copy_content(final_str, str, index);
}

static void	handle_right_padding(char *final_str, char *str, int *index,
		int padding_len)
{
	copy_content(final_str, str, index);
	apply_padding(final_str, index, padding_len, ' ');
}

char	*apply_width_and_padding(char *str, t_format *format, char specifier)
{
	char	*final_str;

	int len_str, total_len, padding_len, index;
	len_str = calculate_string_length(str, specifier);
	set_padding_and_total(len_str, format, &padding_len, &total_len);
	final_str = allocate_string(padding_len, str, format, total_len);
	if (!final_str)
		return (NULL);
	index = 0;
	if (format->flags & FLAG_MINUS)
		handle_right_padding(final_str, str, &index, total_len - len_str);
	else
		handle_left_padding(final_str, str, &index, padding_len, format);
	final_str[total_len] = '\0';
	return (final_str);
}
