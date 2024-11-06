/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:15:20 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/06 09:16:06 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_precision(const char **str)
{
	int	precision;

	precision = -1;
	if (**str == '.')
	{
		precision = 0;
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			precision = precision * 10 + (**str - '0');
			(*str)++;
		}
	}
	return (precision);
}
