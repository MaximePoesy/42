/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:24:10 by staverni          #+#    #+#             */
/*   Updated: 2025/05/19 10:54:06 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	(void)token;
	printf("[%d][%s] ", token->type, token->value);
}

int	get_input(t_shell *sh)
{
	sh->input = read_input(sh->env);
	if (!sh->input)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	lex_input(t_shell *sh)
{
	sh->tokens = lexer(sh->input);
	expand(sh->tokens, sh->env);
	if (!(sh->tokens))
	{
		g_exit_status = 1;
		return (1);
	}
	if (!pre_validate(sh->tokens))
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	parse_input(t_shell *sh)
{
	sh->tree = parse_line(sh->tokens);
	if (!(sh->tree))
	{
		g_exit_status = 1;
		return (1);
	}
	if (!post_validate(sh->tree, sh->env))
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	exec_input(t_shell *sh)
{
	g_exit_status = execution(sh, sh->tree);
	return (g_exit_status);
}
