/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:32:59 by staverni          #+#    #+#             */
/*   Updated: 2025/05/14 18:01:35 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec(t_cmd *cmd, t_list *env)
{
	t_execcmd	*exec;
	char		*path;

	exec = &cmd->u.exec;
	if (!exec->argv[0] || !exec->argv[0][0])
		return (exec_error(NULL), 0);
	path = resolve_cmd_path(exec->argv[0], env);
	if (is_builtin(exec->argv[0]) || !path)
	{
		if (path)
			free(path);
		exec->path = ft_strdup(exec->argv[0]);
		if (!exec->path)
			return (print_error_null("malloc"), 0);
		return (1);
	}
	exec->path = path;
	return (1);
}

int	check_redir(t_cmd *cmd, t_list *env)
{
	if (!cmd->u.redir.cmd || !cmd->u.redir.file || !cmd->u.redir.file[0])
		return (access_error(NULL, 0), 0);
	if (!post_validate(cmd->u.redir.cmd, env))
		return (0);
	return (1);
}

int	post_validate(t_cmd *cmd, t_list *env)
{
	if (!cmd)
		return (print_error_null("no cmd"), 0);
	if (cmd->type == PIPE)
	{
		if (!post_validate(cmd->u.pipe.left, env))
			return (0);
		if (!post_validate(cmd->u.pipe.right, env))
			return (0);
	}
	else if (node_is_redir(cmd->type))
	{
		if (!check_redir(cmd, env))
			return (0);
	}
	else if (cmd->type == CMD)
	{
		if (!check_exec(cmd, env))
			return (0);
	}
	return (1);
}
