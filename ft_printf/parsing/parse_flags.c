/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:13:27 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/06 09:13:56 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_flags(const char **str)
{
	int	flags;

	flags = 0;
	while (**str == '-' || **str == '0' || **str == '.' || **str == '#'
		|| **str == '+' || **str == ' ')
	{
		if (**str == '-')
			flags |= FLAG_MINUS;
		else if (**str == '0')
			flags |= FLAG_ZERO;
		else if (**str == '.')
			flags |= FLAG_DOT;
		else if (**str == '#')
			flags |= FLAG_HASH;
		else if (**str == '+')
			flags |= FLAG_PLUS;
		else if (**str == ' ')
			flags |= FLAG_SPACE;
		(*str)++;
	}
	return (flags);
}
