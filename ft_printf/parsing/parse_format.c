/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:16:25 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/06 09:16:55 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_format	parse_format(const char **str)
{
	t_format	format;

	format = {0, 0, -1};
	format.flags = parse_flags(str);
	format.width = parse_width(str);
	format.precision = parse_precision(str);
	return (format);
}
