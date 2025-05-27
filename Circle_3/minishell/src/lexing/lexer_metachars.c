/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:49:12 by staverni          #+#    #+#             */
/*   Updated: 2025/05/03 16:31:22 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_supported_metachar(const char *c)
{
	if (c[0] == '|' && c[1] == '|')
		return (0);
	if (c[0] == '&' && c[1] == '&')
		return (0);
	else if (c[0] == '(')
		return (0);
	else if (c[0] == ')')
		return (0);
	else if (c[0] == ';')
		return (0);
	else if (c[0] == '&')
		return (0);
	return (1);
}

int	max_metachar_len(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (2);
	return (1);
}
