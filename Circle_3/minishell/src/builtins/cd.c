/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:25:55 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/15 20:37:59 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(char *cwd, t_list **env)
{
	char	newcwd[PATH_MAX];
	char	*oldpwd;
	char	*newpwd;

	if (!getcwd(newcwd, PATH_MAX))
		return (1);
	oldpwd = build_env_string("OLDPWD", cwd);
	newpwd = build_env_string("PWD", newcwd);
	if (oldpwd == NULL || newpwd == NULL)
	{
		print_error_null("cd: malloc error");
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	handle_export_arg(oldpwd, env);
	handle_export_arg(newpwd, env);
	free(oldpwd);
	free(newpwd);
	return (0);
}

static int	go_home(t_list **env)
{
	char	*home;

	home = ft_getenv("HOME", *env);
	if (home == NULL)
	{
		print_error_null("cd: HOME not set");
		free(home);
		return (1);
	}
	if (chdir(home) != 0)
	{
		print_error_null("cd: couldn't find path");
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

static int	go_to_path(int go_old, char *path, char *oldpwd)
{
	if (go_old)
	{
		if (!oldpwd)
		{
			print_error_null("cd: OLDPWD not set");
			return (1);
		}
		if (chdir(oldpwd) != 0)
		{
			print_error_null("cd: couldn't find path");
			return (1);
		}
	}
	else
	{
		if (chdir(path) != 0)
		{
			print_error_null("cd: couldn't find path");
			return (1);
		}
	}
	return (0);
}

int	builtin_cd(t_execcmd *cmd, t_list **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	int		ret;

	if (cmd->argc > 2)
	{
		print_error_null("cd: too many arguments");
		return (1);
	}
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	oldpwd = ft_getenv("OLDPWD", *env);
	if (cmd->argc == 1)
		ret = go_home(env);
	else if (cmd->argc == 2 && ft_strcmp(cmd->argv[1], "-") == 0)
		ret = go_to_path(1, cmd->argv[1], oldpwd);
	else
		ret = go_to_path(0, cmd->argv[1], NULL);
	if (ret == 0)
		ret = update_oldpwd(cwd, env);
	free(oldpwd);
	return (ret);
}
