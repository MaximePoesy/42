/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unquoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:54:09 by staverni          #+#    #+#             */
/*   Updated: 2025/05/01 16:39:27 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_unquoted_loop(t_buffer *buf, char *p, t_list *env)
{
	size_t	consumed_len;

	while (*p && *p != '\"' && *p != '\'')
	{
		consumed_len = 1;
		if (*p == '$')
			consumed_len = apply_dollar_expansion(buf, p, env);
		else if (*p == '\\' && p[1])
			consumed_len = apply_backslash_expansion(buf, p, 1);
		else
			if (!buffer_append(buf, p, 1))
				return (1);
		if (consumed_len < 0)
			return (1);
		p += consumed_len;
	}
	return (0);
}

char	*expand_unquoted(char *token, t_list *env)
{
	char		*p;
	char		*append;
	int			loop_status;
	t_buffer	buf;

	if (!token)
		return (print_error_null("Error: expansion failed"));
	if (!buffer_init(&buf, 64))
		return (print_error_null("Error: buffer initialization failed"));
	p = token;
	if (*p == '\"')
		++p;
	loop_status = expand_unquoted_loop(&buf, p, env);
	if (loop_status == 1)
	{
		buffer_free_data(&buf);
		return (print_error_null("Error: expansion failed"));
	}
	if (assign_buffer(&buf, &append))
		return (print_error_null("Error: buffer assignment failed"));
	return (append);
}
