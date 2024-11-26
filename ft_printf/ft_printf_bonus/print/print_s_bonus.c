/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:43:24 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/19 10:48:39 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int     print_s(char *str, t_format *format)
{
        int             num_char;
        char    *new_str;
        char    *test;

        if (!str)
        {
                new_str = "(null)";
                write(1, new_str, 6);
                return (6);
        }
        test = ft_strdup(str);
        new_str = apply_flags(test, format, 's');
        if (!new_str)
        {
                free(new_str);
                return (0);
        }
        num_char = ft_strlen(new_str);
        write(1, new_str, num_char);
        free(new_str);
        return (num_char);
}

