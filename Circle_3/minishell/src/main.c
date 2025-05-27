/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:02:52 by staverni          #+#    #+#             */
/*   Updated: 2025/05/18 09:38:05 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static int	set_shlvl(t_shell *sh)
{
	char	*shlvl_str;
	char	*shlvl_env;

	shlvl_env = ft_getenv("SHLVL", sh->env);
	if (!shlvl_env)
	{
		write(2, "Minishell initialization failed\n", 25);
		g_exit_status = 1;
		return (1);
	}
	shlvl_str = ft_itoa(ft_atoi(shlvl_env) + 1);
	free(shlvl_env);
	shlvl_env = build_env_string("SHLVL", shlvl_str);
	free(shlvl_str);
	if (!shlvl_env)
	{
		write(2, "Minishell initialization failed\n", 25);
		g_exit_status = 1;
		return (1);
	}
	handle_export_arg(shlvl_env, &(sh->env));
	free(shlvl_env);
	return (0);
}

static int	init_shell(t_shell *sh)
{
	set_signals();
	sh->env = environ_to_list();
	if (!sh->env)
	{
		write(2, "Minishell initialization failed\n", 25);
		g_exit_status = 1;
		return (1);
	}
	handle_export_arg("SHELL=minishell", &(sh->env));
	if (set_shlvl(sh))
		return (1);
	return (0);
}

void	clean_shell(t_shell *sh)
{
	if (sh->input)
	{
		free(sh->input);
		sh->input = NULL;
	}
	if (sh->tokens)
	{
		ft_token_iter(sh->tokens, free_token);
		sh->tokens = NULL;
	}
	if (sh->tree)
	{
		free_cmd_tree(sh->tree);
		sh->tree = NULL;
	}
}

void	exit_shell(t_shell *sh, int status)
{
	clean_shell(sh);
	ft_lstclear(&(sh->env), free);
	rl_clear_history();
	exit(status);
}

int	main(void)
{
	t_shell	sh;

	sh = (t_shell){0};
	if (init_shell(&sh))
		return (1);
	while (1)
	{
		clean_shell(&sh);
		if (get_input(&sh))
		{
			if (sh.input == NULL)
				break ;
			if (sh.input[0] == '\0')
				continue ;
		}
		if (lex_input(&sh))
			continue ;
		if (parse_input(&sh))
			continue ;
		if (exec_input(&sh))
			continue ;
	}
	write(1, "exit\n", 5);
	exit_shell(&sh, 0);
}
